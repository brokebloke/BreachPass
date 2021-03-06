#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Attempt at multi OS support, not in use*/
/*
#if defined (__linux__)
const char defaultConfigPath()
{
  char *homeDir = malloc(sizeof(char));
  strcpy(asd, getenv("HOME"));
  strcat(asd, "/.BreachPass");
  return homeDir;
}

#elif defined(__APPLE__) && defined(__MACH__)
const char defaultConfigPath()
{
    char *homeDir = malloc(sizeof(char));
    strcpy(homeDir, getenv("HOME"));
    strcat(homeDir, "/Library/Application Support/BreachPass");
    return homeDir;
}

#endif
*/

/* Gets the PATH of the current user, slightly buggy */
char *getPWMPath()
{
  FILE *fp;
  char *temp = malloc(500);
  char *path = malloc(500);
  fp = popen("which lpass", "r");

  while(fgets(temp, sizeof(temp), fp) != NULL)
  {
    strcat(path, temp);
  }
  strtok(path, "\n");
  pclose(fp);
  return path;
}

/* Standardizes file opening so that a command and path can be run, while properly reading the stream and properly outputting the data in a char array*/
/* Most of this code was borrowed from a generous coder */

char *runCommand(char cmd[], char pwmpath[])
{
  char buf[100];
  char *str = NULL;
  char *temp = NULL;
  char *fullcmd = malloc(sizeof(char));
  strcpy(fullcmd, pwmpath);
  strcat(fullcmd, " ");
  strcat(fullcmd, cmd);
  unsigned int size = 1;  // start with size of 1 to make room for null terminator
  unsigned long strlength;

  /* Opens file with crafted string, exits on failure */
  FILE *ls;
  if (NULL == (ls = popen(fullcmd, "r"))) {
    perror("popen");
    exit(EXIT_FAILURE);
  }

  while (fgets(buf, sizeof(buf), ls) != NULL) {
    strlength = strlen(buf);
    temp = realloc(str, size + strlength);  // allocate room for the buf that gets appended
    if (temp == NULL) {
      // allocation error
    } else {
      str = temp;
    }
    strcpy(str + size - 1, buf);     // append buffer to str
    size += strlength; 
  }
  pclose(ls);
  return str;
}

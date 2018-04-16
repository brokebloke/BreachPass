#include <stdio.h>
#include <strings.h>
#include <stdbool.h>

/* String compares against domain and the haveibeenpwend database and returns true if a match is found */
bool checkDomainAgainstBreach(char lpassdata[], char pwnedata[])
{
    char a[200];
    char line[100];
    FILE *ls = fmemopen(pwnedata, strlen(pwnedata), "r");
    while(fgets(line,sizeof(line), ls) != NULL)
    {
        strtok(line, "\n");
        if(sscanf(lpassdata, "%*[^/]%*[/]%[^/]", a) == 1)
        {
            if(strcasestr(a, line) == a)
            {
                fclose(ls);
                return true;
            }
        }
        strcat(line, "\n");
    }
    fclose(ls);
    return false;
}

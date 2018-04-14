#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

/* Defines all methods as per C99 */
char *runCommand(char cmd[], char pwmpath[]);
bool checkDomainAgainstBreach(char lpassdata[], char pwnedata[]);
char *pullDatabaseData(char *data);
int http_get_response(void *buffer, size_t size, size_t rxed, char **msg_in);
bool lpassVerifyStatus(char input[]);
char *lpassGetID(char *str);
char *lpassGetData(char input[], char *str, char path[]);
char *getPWMPath();
char *runCommand(char cmd[], char pwmpath[]);
bool pythonIO(char username[], char password[], char newpassword[], char domain[]);
char *lpassGeneratePassword(char path[]);
void lpassChangePassword(char id[], char newpass[], char path[]);


int main()
{
    /* Checks to see if the user is logged in, if not exits the program */
    if (lpassVerifyStatus(runCommand("ls", "/usr/local/bin/lpass")) == true)
    {
        return 0;
    }
    char line[1000], line2[1000], line3[1000]; //Used for fgets newlines when being read
    
    /* Runs methods and stores char array to each one */
    char * id = lpassGetID(runCommand("ls", "/usr/local/bin/lpass"));
    char * domain = lpassGetData("domain", id, "/usr/local/bin/lpass");
    char * email = lpassGetData("user", id, "/usr/local/bin/lpass");
    char * password = lpassGetData("password", id, "/usr/local/bin/lpass");
    char * newpassword = lpassGeneratePassword("/usr/local/bin/lpass");
    char * matchdata = malloc(5000);
    
    /* Stores char array from memory into FILE format so it can be read through fgets*/
    FILE *ls = fmemopen(email, strlen(email), "r");
    FILE *ls1 = fmemopen(domain, strlen(domain), "r");
    FILE *ls2 = fmemopen(password, strlen(password), "r");
    
    /* Each while loop, loops through the line, separated by newline*/
    while (fgets(line, sizeof(line), ls) != NULL)
    {
        while(fgets(line2, sizeof(line2), ls1) != NULL)
        {
            while(fgets(line3, sizeof(line3), ls2) != NULL)
            {
                /*Removes the newline so that it gets the actual data*/
                strtok(line, "\n");
                strtok(line2, "\n");
                strtok(line3, "\n");
                strcpy(matchdata, pullDatabaseData(line)); // Pulls data from haveibeenpwned
                if(checkDomainAgainstBreach(line2, matchdata) == true) // Checks if checkDomainAgainstBreach = true
                {
                    if(pythonIO(line, line3, newpassword, line2) == true) // Checks if pythonIO equals true
                    {
                        lpassChangePassword(line, newpassword, runCommand("generate", "/usr/local/bin/lpass")); // Changes the password in LastPass
                    }
                }
                strcat(line3, "\n"); // Adds newline back to fix loop from breaking
                sleep(2); // Slows the program to stop aggressive API aggregation
            }
            strcat(line2, "\n");// Adds newline back to fix loop from breaking
        }
        strcat(line, "\n");// Adds newline back to fix loop from breaking
    }
    /* closes streams and returns 0*/
    fclose(ls);
    fclose(ls1);
    fclose(ls2);
    return 0;
}

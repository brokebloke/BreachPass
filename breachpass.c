#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

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
    char line[1000], line2[1000], line3[1000];
    char * id = lpassGetID(runCommand("ls", "/usr/local/bin/lpass"));
    char * domain = lpassGetData("domain", id, "/usr/local/bin/lpass");
    char * email = lpassGetData("user", id, "/usr/local/bin/lpass");
    char * password = lpassGetData("password", id, "/usr/local/bin/lpass");
    char * newpassword = lpassGeneratePassword("/usr/local/bin/lpass");
    char * matchdata = malloc(5000);
    FILE *ls = fmemopen(email, strlen(email), "r");
    FILE *ls1 = fmemopen(domain, strlen(domain), "r");
    FILE *ls2 = fmemopen(password, strlen(password), "r");
    while (fgets(line, sizeof(line), ls) != NULL)
    {
        while(fgets(line2, sizeof(line2), ls1) != NULL)
        {
            while(fgets(line3, sizeof(line3), ls2) != NULL)
            {
                strtok(line, "\n");
                strtok(line2, "\n");
                strtok(line3, "\n");
                strcpy(matchdata, pullDatabaseData(line));
                if(checkDomainAgainstBreach(line2, matchdata) == true)
                {
                    if(pythonIO(line, line3, newpassword, line2) == true)
                    {
                        lpassChangePassword(line, newpassword, runCommand("generate", "/usr/local/bin/lpass"));
                    }
                }
                strcat(line3, "\n");
                sleep(2);
            }
            strcat(line2, "\n");
        }
        strcat(line, "\n");
    }
    fclose(ls);
    fclose(ls1);
    fclose(ls2);
    return 0;
}

/*void createData()
{
	struct stat st = {0};

	if (stat(defaultConfigPath(), &st) == -1) 
	{
    	mkdir(defaultConfigPath(), 0700);
	}
	else if (stat(defaultConfigPath() + "/config.txt", &st) == -1)
	{
		mkdir(defaultConfigPath() + "/config.txt", 0777);
	}
	else if (stat(defaultConfigPath() + "/data.txt", &st) == -1)
	{
		mkdir(defaultConfigPath() + "/data.txt", 0777);
	}
}*/

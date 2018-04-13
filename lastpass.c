#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

bool lpassVerifyStatus(char input[])
{
	char notlogged[] = "Not logged in.";
    char notlogged2[] = "Master Password:";
	if (strcmp(input, notlogged) || strcmp(input, notlogged2))
	{
		return false;
	}
	else
	{
		return true;
	}
}

char *lpassGetID(char *str)
{
    char line[500] = {0};
    long id;
    char **array = malloc(5000);
    char *temp = malloc(5000);
    FILE *ls = fmemopen(str, strlen(str), "r");

    while ( fgets ( line, sizeof (line), ls) ) {
        if ( ( sscanf ( line, "%*[^:]%*[^ ] %ld[^]]%*[^\n]" , &id)) == 1) 
        {
          sprintf(temp, "%ld", id);
        }
        strcat(array, temp);
        strcat(array, "\n");
    }

    fclose(ls);
    return array;
}

char *lpassGetData(char input[], char *str, char path[])
{
    FILE *pf = NULL, *ls = NULL;
    char line[500] = {0};
    char line2[500] = {0};
    char data[500] = {0};
    char **user = malloc(5000);
    char **domain = malloc(5000);
    char **password = malloc(5000);
    char *str2 = malloc(5000);
    pf = fmemopen(str, strlen(str), "r");

    while (fgets (line, sizeof(line), pf) != NULL)
    {
        strcpy(str2, path);
        strcat(str2, " show");
        strcat(str2, " ");  
        strcat(str2, line);
        ls = popen(str2, "r");
        while (fgets (line2, sizeof(line2), ls) != NULL)
        {
            if(strstr(line2, "Username:") != NULL && strcmp(input, "user") == 0)
            {
                if ( ( sscanf ( line2, "%*[^:]%*[^ ] %s%*[^\n]" , data)) == 1)
                {
                    strcat(user, data);
                    strcat(user, "\n");
                }
            }
            else if(strstr(line2, "Password:") != NULL && strstr(line2, "http") == NULL && strcmp(input, "password") == 0)
            {
                if ( ( sscanf ( line2, "%*[^:]%*[^ ] %s%*[^\n]" , data)) == 1)
                {
                    strcat(password, data);
                    strcat(password, "\n");
                }
            }
            else if(strstr(line2, "URL:") != NULL && strcmp(input, "domain") == 0)
            {
                if(strstr(line2, "https://") != NULL || strstr(line2, "htto://") != NULL)
                {
                    if ( ( sscanf ( line2, "%*[^:]%*[^ ] %s%*[^\n]" , data)) == 1)
                    {
                        strcat(domain, data);
                        strcat(domain, "\n");
                    }
                }
            }
        }
    }
    //fclose(ls);
    //fclose(pf);
    if(strcmp(input, "user") == 0)
    {
        return user;
    }
    else if(strcmp(input, "password") == 0)
    {
        return password;
    }
    else if(strcmp(input, "domain") == 0)
    {
        return domain;
    }
    return 0;
}

char *lpassGeneratePassword(char path[])
{
    char *str = malloc(100);
    char *str2 = malloc(20);
    char line[100];
    strcpy(str, path);
    strcat(str, " password 20");
    FILE *fp = popen(str, "r");
    while(fgets(line, sizeof(line), fp) != NULL)
    {
        strtok(line, "\n");
        strcpy(str2, line);
    }
    fclose(fp);
    return str2;
}

void lpassChangePassword(char id[], char newpass[], char path[])
{
    char *str = malloc(500);
    char line[100];
    strcpy(str, path);
    strcat(str, "edit ");
    strcat(str, id);
    strcat(str, " -p ");
    strcat(str, newpass);
    FILE *fp = popen(str, "r");
    pclose(fp);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

/* Checks to see if the command ran has these strings, returns true if found */
bool lpassVerifyStatus(char input[])
{
	char notlogged[] = "Not logged in.";
    char notlogged2[] = "Master Password:";
	if (strcmp(input, notlogged) || strcmp(input, notlogged2))
	{
		return true;
	}
    return false;
}
/* Gathers all ID's that the user has. ID's have information such as username, passwords, domains, etc stored within */
char *lpassGetID(char *str)
{
    char line[500] = {0};
    long id;
    char **array = malloc(5000);
    char *temp = malloc(5000);
    FILE *ls = fmemopen(str, strlen(str), "r");

    while ( fgets ( line, sizeof (line), ls) ) { // Reads each line created
        if ( ( sscanf ( line, "%*[^:]%*[^ ] %ld[^]]%*[^\n]" , &id)) == 1) // Filters data specifically so that only the ID is taken
        {
          sprintf(temp, "%ld", id); // Converts the Long Decimal back to char array for formatting purposes.
        }
        strcat(array, temp);
        strcat(array, "\n");
    }

    fclose(ls);
    return array;
}

/* Gathers data from the ID */
char *lpassGetData(char input[], char *str, char path[])
{
    FILE *pf = NULL, *ls = NULL;
    char line[500] = {0};
    char line2[500] = {0};
    char data[500] = {0};
    char **user = malloc(5000); // stores user
    char **domain = malloc(5000); // stores domain
    char **password = malloc(5000); // stores password
    char *str2 = malloc(5000);
    pf = fmemopen(str, strlen(str), "r");

    while (fgets (line, sizeof(line), pf) != NULL)
    {
        strcpy(str2, path);
        strcat(str2, " show");
        strcat(str2, " ");  
        strcat(str2, line);
        ls = popen(str2, "r");
        while (fgets (line2, sizeof(line2), ls) != NULL) // Loops through the data each by newline
        {
            if(strstr(line2, "Username:") != NULL && strcmp(input, "user") == 0) // Finds data with Username and with the input defined as user, then filters and stores data
            {
                if ( ( sscanf ( line2, "%*[^:]%*[^ ] %s%*[^\n]" , data)) == 1)
                {
                    strcat(user, data);
                    strcat(user, "\n");
                }
            }
            else if(strstr(line2, "Password:") != NULL && strstr(line2, "http") == NULL && strcmp(input, "password") == 0) // Finds data with Password and filters out domains and with input defined as password
            {
                if ( ( sscanf ( line2, "%*[^:]%*[^ ] %s%*[^\n]" , data)) == 1)
                {
                    strcat(password, data);
                    strcat(password, "\n");
                }
            }
            else if(strstr(line2, "URL:") != NULL && strcmp(input, "domain") == 0) // Finds data sored with URL and http/https tags, then filters everything that isnt a domain.
            {
                if(strstr(line2, "https://") != NULL || strstr(line2, "http://") != NULL)
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
    
    /* Not closing the file streams due to memory access errors */
    //fclose(ls);
    //fclose(pf);
    
    /* Returns the correct char array that is stored */
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

/* Runs the command to generate a password and returns the generated password */
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

/* Changes the password as by executing the command with the data provided */
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PYTHON "/usr/local/bin/python3"
#define SCRIPT "website.py"

bool pythonIO(char username[], char password[], char newpassword[], char domain[])
{
    int response;
    char * path = malloc(1000);
    strcpy(path, PYTHON);
    strcat(path, " ");
    strcat(path, SCRIPT);
    strcat(path, " ");
    strcat(path, username);
    strcat(path, " ");
    strcat(path, password);
    strcat(path, " ");
    strcat(path, newpassword);
    strcat(path, " ");
    strcat(path, domain);
    
    FILE* in = popen(path, "r");
    fscanf(in, "%d", &response);
    if(response == 200)
    {
        return true;
    }
    return false;
}

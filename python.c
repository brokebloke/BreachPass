#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PYTHON "/usr/local/bin/python3"
#define SCRIPT "website.py"

/* Sends a crafted response to a python script that will handle changing the password from the website*/
bool pythonIO(char username[], char password[], char newpassword[], char domain[])
{
    // Looks like this: /usr/local/bin/python3 website.py $username $password $newpassword $domain
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
    // Opens the file with the char array and waits for the response (200). Returns true if response equals 200.
    FILE* in = popen(path, "r");
    fscanf(in, "%d", &response);
    if(response == 200)
    {
        return true;
    }
    return false;
}

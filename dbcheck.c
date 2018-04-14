#include <stdio.h>
#include <strings.h>
#include <stdbool.h>

/* String compares against domain and the haveibeenpwend database and returns true if a match is found */
bool checkDomainAgainstBreach(char lpassdata[], char pwnedata[])
{
    char *a;
    a = strtok(lpassdata, ".:/");
    while(a != NULL)
    {
        if(strcasecmp(a, pwnedata) == 0)
        {
            return true;
        }
        a = strtok(NULL, ".:/");
    }
    return false;
}

#include <stdio.h>
#include <strings.h>
#include <stdbool.h>

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
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

int http_get_response(void *buffer, size_t size, size_t rxed, char **msg_in); // Xcode requires it to be defined here because of it's use

/* Pulls data from a crafted URL defined as url, then sends the output to a string, tokenizes the format to be read as newlines and returns the char array*/
char *pullDatabaseData(char *data) 
{
    char url[200];
    strcpy(url, "https://haveibeenpwned.com/api/v2/breachedaccount/");
    strcat(url, data);
    strcat(url, "?truncateResponse=true");
    CURL **curl = curl_easy_init();
    char *msg_in = calloc(1,sizeof(char));
    char **strout = malloc(5000);
    char *a;
    int x = 0;
    if(curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "BreachPass/1.0"); // Required for haveibeenpwned

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_get_response); // writes response to return nothing (required in order to write data)
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &msg_in); // writes data to a char array and returns it
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    a = strtok(msg_in, "[{,\"}]"); // Tokenizes the data retrieved
    while(a != NULL) // Loops through the tokenized data
    {
        if(x % 2 != 0) // Grabs the odd data from (Name\nData\nName\nData)
        {
            strcat(strout, a);
            strcat(strout, "\n"); // Adds newline for formatting
        }
        a = strtok(NULL, "[{,\":}]"); // Reapplies tokenizes format in case it's not applied
        x++;
    }
    return strout;
}

/* Grabs input data stream and returns it as nothing, then frees the data and returns the stream size */
int http_get_response(void *buffer, size_t size, size_t rxed, char **msg_in)
{
    char *c;

    if (asprintf(&c, "%s%.*s", *msg_in, size * rxed, buffer) == -1) {
        free(*msg_in);
        msg_in = NULL;
        return -1;
    }

    free(*msg_in);
    *msg_in = c;

    return size * rxed;
}

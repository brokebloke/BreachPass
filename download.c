#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

int http_get_response(void *buffer, size_t size, size_t rxed, char **msg_in);

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
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "BreachPass/1.0");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, http_get_response);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &msg_in);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    a = strtok(msg_in, "[{,\"}]");
    while(a != NULL)
    {
        if(x % 2 != 0)
        {
            strcat(strout, a);
            strcat(strout, "\n");
        }
        a = strtok(NULL, "[{,\":}]");
        x++;
    }
    return strout;
}


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

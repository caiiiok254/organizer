#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>
#include "functions.h"
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
int notepadpw()
{
    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, "http://notepad.pw");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        res = curl_easy_perform(curl);
        if(res == CURLE_OK) {
            char *url = NULL;
            curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
            FILE *result;
            result = fopen("NotepadList.txt", "a+");
            char name[100];
            printf("Enter your notepad name: \n");
            scanf("%s", name);
            if(url)
                fprintf(result, "%s : %s\n", name, url);
            printf("Wait some, browser should appear in a second.. \n");
            char *firefox = "firefox --new-window ";
            char *firefoxurl = concat(firefox, url);
            system(firefoxurl);
            system ("clear");
            fclose(result);
        }
        curl_easy_cleanup(curl);
        char choice[10];
        printf("Do you want to add more notepad? y/n \n");
        scanf("%s", choice);
        if (strcmp(choice, "y") == 0) return notepadpw();
        return main();
    }
}
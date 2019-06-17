#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>
#include "functions.h"

int browser()
{
    printf("Please enter the url to visit or choose from list below \n");
    printf("List of available url: \n");
    printf("1. EIOS system\n");
    printf("2. Study calendar\n");
    printf("or enter your own url...\n");
    char url[200];
    scanf("%s", url);
    if (strlen(url) > 200) {
        printf("Url length is too big, please enter smaller url!");
        return browser();
    }
    if (strcmp(url, "1") == 0) {
        system("firefox --new-window https://eios.sibsutis.ru");
    } else if (strcmp(url, "2") == 0) {
        system("firefox --new-window https://sibsutis.ru/about/calendar.php");
    } else {
        char *firefox = "firefox --new-window ";
        char *firefoxurl = concat(firefox, url);
        system(firefoxurl);
    }
    char choice[10];
    printf("Do you want to open another url? y/n \n");
    scanf("%s", choice);
    if (strcmp(choice, "y") == 0) return browser();
    return main();
}
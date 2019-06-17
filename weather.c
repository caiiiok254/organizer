#include <stdio.h>
#include <curl/curl.h>
#include "functions.h"

int weather()
{
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://wttr.in");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.47.1");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "Curl error, provide this information to developer: %s\n",
                    curl_easy_strerror(res));
        curl_easy_cleanup(curl);

    }
    return main();
}
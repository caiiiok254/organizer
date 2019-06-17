#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>
#include "functions.h"

void extra_symbol(char* file, size_t size)
{
    if ((file[size] == '<') && (file[size + 1] == 'b') && (file[size + 2] == 'r') && (file[size + 3] == '>')) { //<br>
        file[size] = ' ';
        file[size + 1] = ' ';
        file[size + 2] = ' ';
        file[size + 3] = '\n';
    }
    if ((file[size] == '<') && (file[size + 1] == 'b') && (file[size + 2] == 'r') && (file[size + 3] == ' ')
        && (file[size + 4] == '/') && (file[size + 5] == '>')) { //<br />
        file[size] = ' ';
        file[size + 1] = ' ';
        file[size + 2] = ' ';
        file[size + 3] = ' ';
        file[size + 4] = ' ';
        file[size + 5] = '\n';
    }
    if ((file[size] == '&') && (file[size + 1] == 'l') && (file[size + 2] == 't') && (file[size + 3] == ';')) { //&lt;
        file[size] = ' ';
        file[size + 1] = ' ';
        file[size + 2] = ' ';
        file[size + 3] = ' ';
    }
    if ((file[size] == '&') && (file[size + 1] == 'g') && (file[size + 2] == 't') && (file[size + 3] == ';')) { //&gt;
        file[size] = ' ';
        file[size + 1] = ' ';
        file[size + 2] = ' ';
        file[size + 3] = ' ';
    }
    if ((file[size] == '&') && (file[size + 1] == 'q') && (file[size + 2] == 'u') && (file[size + 3] == 'o') && (file[size + 4] == 't') && (file[size + 5] == ';')) {//&quot;
        file[size] = ' ';
        file[size + 1] = ' ';
        file[size + 2] = ' ';
        file[size + 3] = '"';
        file[size + 4] = '"';
        file[size + 5] = ' ';
    }
}

void parsing_quotes(char* file, long fsize)
{
    FILE* out = fopen("exit.html", "w");
    if (out == NULL) {
        return;
    }
    size_t start = 0, end = 0, new_start = 0, new_end = 0;
    for (size_t size = 0; size < (size_t)fsize; size++) {
        extra_symbol(file, size);
        if ((file[size] == 'q') && (file[size + 1] == 'u') && (file[size + 2] == 'o') && (file[size + 3] == 't')
            && (file[size + 4] == 'e') && (file[size + 5] == '_') && (file[size + 6] == '_') && (file[size + 7] == 'b')
            && (file[size + 8] == 'o') && (file[size + 9] == 'd') && (file[size + 10] == 'y')) { //quote__body
            size += 19;
            new_start = size;
        }
        if ((file[size + 1] == '<') && (file[size + 2] == '/') && (file[size + 3] == 'd')
            && (file[size + 4] == 'i') && (file[size + 5] == 'v') && (file[size + 6] == '>')) { //</div>
            new_end = size;
        }
        if ((new_start != start) && (new_end != end) && (new_start < new_end)) {
            size_t temp_start = new_start;
            start = new_start;
            end = new_end;
            char* quote = (char*)calloc(1, new_end - new_start + 1);
            for (size_t i = 0; temp_start < new_end; temp_start++, i++) {
                quote[i] = file[temp_start];
            }
            printf("%s\n---------------------------------------------------------------------------------------------------------------\n", quote);
            fprintf(out, "%s\n---------------------------------------------------------------------------------------------------------------\n", quote);
            free(quote);
        }
    }
    fclose(out);
}

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

int bashim() {
        CURL *curl_handle;
        static const char *pagefilename = "quote.html";
        FILE *pagefile;
        curl_global_init(CURL_GLOBAL_ALL);
        curl_handle = curl_easy_init();
        char *url_string = "https://bash.im/random?7013";
        curl_easy_setopt(curl_handle, CURLOPT_URL, url_string);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
        pagefile = fopen(pagefilename, "wb");
        if(pagefile) {
            curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);
            curl_easy_perform(curl_handle);
            fclose(pagefile);
        }
        curl_easy_cleanup(curl_handle);
        curl_global_cleanup();

        FILE* in = fopen("quote.html", "r");
        if (in == NULL) {
            printf("File read error!");
            return 0;
        }
        fseek(in, 0, SEEK_END);
        long fsize = ftell(in);
        rewind(in);
        char* file = (char*)calloc(1, fsize + 1);
        if (file == NULL) {
            printf("File read error!");
            return 0;
        }
        fread(file, fsize + 1, 1, in);
        fclose(in);
        parsing_quotes(file, fsize);
        free(file);
        char choice[10];
        printf("Do you want to see more quotes? y/n \n");
        scanf("%s", choice);
        if (strcmp(choice, "y") == 0) return bashim();
        return fun();
        }

int starwars()
{
    printf("Prepare for a long-long story...");
    system("telnet towel.blinkenlights.nl");
    return fun();
}

int fun()
{
    printf("Choose one option below\n");
    printf("1. Bash.im quotes to read\n");
    printf("2. Star Wars in ascii\n");
    printf("3. Return to main page\n");
    int choice;
    scanf("%d", &choice);
    switch(choice) {
        case 1:
            bashim();
            break;
        case 2:
            starwars();
            break;
        case 3:
            return main();
            break;
        default:
            printf("Error! Please enter the number of selected option!\n");
            return fun();
    }
}
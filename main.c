#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>
#include "functions.h"

int main() {
    printf("Organizer menu: \n");
    printf("1. Notepad online\n");
    printf("2. Check the weather\n");
    printf("3. IP check\n");
    printf("4. Open browser on selected page\n");
    printf("5. Fun page\n");
    printf("6. Close the program\n");
    int choice;
    scanf("%d", &choice);
    switch(choice) {
        case 1:
            notepadpw();
            break;
        case 2:
            weather();
            break;
        case 3:
            ipcheck();
            break;
        case 4:
            browser();
            break;
        case 5:
            fun();
            break;
        case 6:
            return 0;
        default:
            printf("Error! Please enter the number of selected page!\n");
            return main();
    }
}
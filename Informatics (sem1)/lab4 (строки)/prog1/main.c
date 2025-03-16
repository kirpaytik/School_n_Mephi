#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include "myfuncs.h"

int main()
{
    char *stroka = NULL;
    int number;
    int fl;
    do {
        stroka = readline("Input a string\n");
        printf("\n");
        if (stroka == NULL || strlen(stroka) == 0) {
            break;
        }

        printf("Input a number\n");
        fl = safeScanfInt(&number);
        printf("\n");
        if (fl == 0) {
            break;
        }

        func(stroka, number);
        printf("Output string:\n");
        printf("\"%s\"\n\n", stroka);
    } while (stroka != NULL && fl != 0);

    printf("Ending the program\n");
    free(stroka);
    return 0;
}

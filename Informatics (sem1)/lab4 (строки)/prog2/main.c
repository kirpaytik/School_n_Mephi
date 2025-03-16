#include <stdio.h>
#include <stdlib.h>
#define space " "
#define spacetab " \t"
#include "myfuncs.h"
#include "mystringh.h"

int main()
{
    char *stroka = NULL;
    int number;
    int fl;
    do {
        stroka = readl("Input a string\n");
        printf("\n");
        if (stroka == NULL || slen(stroka) == 0) {
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

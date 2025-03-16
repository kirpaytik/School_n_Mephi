#include <stdio.h>
#include <stdlib.h>
#include "safeScanfDouble.h"

int safeScanfDouble (double *target)
{
    int guard;
    int flag = 1;
    while (flag == 1) {
        guard = scanf("%lf",target);
        scanf("%*[^\n]");
        if (guard == EOF) {
            printf("Завершение программы.\n");
            return 0;
        }
        if (guard < 1) {
            printf("Введите число!\n");
            continue;
        }
        flag = 0;
    }
    return 1;
}
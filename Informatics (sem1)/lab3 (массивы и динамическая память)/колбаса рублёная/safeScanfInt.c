#include <stdio.h>
#include <stdlib.h>
#include "safeScanfInt.h"

int safeScanfInt (int *target, int panel)
{
    int guard;
    int flag = 1;
    while (flag == 1) {
        guard = scanf("%d",target);
        scanf("%*[^\n]");
        if (guard == EOF) {
            printf("Завершение программы.\n");
            return 0;
        }
        if (guard < 1) {
            switch (panel) {
            case 0:
                printf("Введите целое число от 1 до 6!\n");
                break;
            case 1:
            case 22:
                printf("Введите целое число не меньше 0!\n");
                break;
            case 3:
                printf("Введите целое число не меньше 0 и меньше длины массива!\n");
            }
            continue;
        }
        flag = 0;
    }
    return 1;
}
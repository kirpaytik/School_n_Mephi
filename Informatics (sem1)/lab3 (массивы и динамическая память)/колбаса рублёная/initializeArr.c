#include <stdio.h>
#include <stdlib.h>
#include "initializeArr.h"
#include "safeScanfDouble.h"

int initializeArr (double **arr, int len)
{
    double *temp;
    if (*arr == NULL) {
        temp = (double*)malloc(len * sizeof(double));
    }
    else {
        temp = (double*)realloc(*arr, len * sizeof(double));
    }
    if (temp == NULL) {
        printf("Не найдена свободная память для инициализации нового массива\n");
        return 0;
    }
    
    *arr = temp;
    int i;
    int returned;
    printf("Введите элементы массива\n");
    for (i = 0; i < len; ++i) {
        returned = safeScanfDouble( &((*arr)[i]) );
        if (returned == 0) {
            return -1;
        }
    }
    return 1;
}
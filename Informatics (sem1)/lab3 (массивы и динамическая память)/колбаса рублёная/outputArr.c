#include <stdio.h>
#include <stdlib.h>
#include "outputArr.h"

void outputArr (double *arr, int len)
{
    if (len == 0) {
        printf("Массив не проинициализирован\n");
        return;
    }
    int i;
    for (i = 0; i < len; ++i) {
        printf("%lf ", arr[i]);
    }
    printf("\n");
}
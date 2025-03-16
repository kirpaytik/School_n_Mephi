#include <stdio.h>
#include <stdlib.h>
#include "insertElem.h"

void insertElem (double **arr, int *len, double elem, int ind)
{
    double *temp;
    if (*arr == NULL) {
        temp = (double*)malloc(((*len) + 1) * sizeof(double));
    }
    else {
        temp = (double*)realloc(*arr, ((*len) + 1) * sizeof(double));
    }
    if (temp == NULL) {
        printf("Не найдена свободная память для инициализации нового массива\n");
        return;
        // return 0;
    }
    
    *arr = temp;
    (*len)++;
    int i;
    for (i = (*len)-1; i > ind; --i) {
        (*arr)[i] = (*arr)[i-1];
    }
    (*arr)[ind] = elem;
    // return 1;
}
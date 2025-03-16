#include <stdio.h>
#include <stdlib.h>
#include "removeElem.h"

void removeElem (double **arr, int *len, int ind)
{
    int i;
    for (i = ind; i < (*len)-1; ++i) {
        (*arr)[i] = (*arr)[i+1];
    }
    
    if (*len == 1) {
        free(arr);
        *arr = NULL;
        *len = 0;
        return;
    }
    
    double *temp;
    if (*arr == NULL) {
        temp = (double*)malloc(((*len) - 1) * sizeof(double));
    }
    else {
        temp = (double*)realloc(*arr, ((*len) - 1) * sizeof(double));
    }
    if (temp == NULL) {
        printf("Не найдена свободная память для инициализации нового массива\n");
        printf("Выбранный элемент удалён без уменьшения длины массива\n");
        return;
        // return 0;
    }
    
    *arr = temp;
    (*len)--;
    // return 1;
}
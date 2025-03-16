#include <stdio.h>
#include <stdlib.h>
#include "individualTask.h"
#include "intFlComp.h"
#include "removeElem.h"

void individualTask(double **arr, int *len)
{
    if (*len == 0) {
        printf("Нет цели для выполонения действия: массив не проинициализирован.\n");
        return;
    }
    int i;
    for (i = 0; i < *len; ++i) {
        if ( 1 - intFlComp((*arr)[i]) ) {
            removeElem(arr, len, i);
            i--;
        }
    }
}
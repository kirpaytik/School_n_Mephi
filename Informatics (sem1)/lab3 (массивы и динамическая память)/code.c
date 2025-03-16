#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int initializeArr (double**, int);
void insertElem (double**, int*, double, int);
void removeElem (double**, int*, int);
void individualTask(double**, int*);
void outputArr (double*, int);

int intFlComp (double);
int safeScanfInt (int*, int);
int safeScanfDouble (double*);

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

int intFlComp (double number)
{
    double doppelIntN;
    double doppelFloatN;
    doppelFloatN = modf(number,&doppelIntN);
    int intN = (int)doppelIntN;
    
    // printf("%lf\n%d %lf\n", number, intN, floatN);
    if (intN == 0) {
        if (number != 0) {
            return 1;
        }
        else {
            return 0;
        }
    }

    int lenIntN = (int)floor(log10(abs(intN))) + 1;
    // printf("%d\n",lenIntN);
    int i;
    for (i = 0; i < lenIntN; i++) {
        doppelFloatN *= 10;
    }
    int floatN = (int)round(doppelFloatN);
    // printf("%d %lf %d\n", intN, doppelFloatN, floatN);
    if (abs(floatN) > abs(intN)) {
        return 1;
    }
    return 0;
}

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

int main()
{
    double *arr = NULL;
    int len = 0, lencopy;
    
    int fl = 1;
    int panel;
    int returned;
    double elem;
    int ind;
    while (fl == 1) {
        panel = -1; ind = -1;
        printf("Выберите одну из опций:\n\
            (1) Инициализация массива\n\
            (2) Вставка нового элемента\n\
            (3) Удаление элемента\n\
            (4) Индивидуальное задание\n\
            (5) Вывод содержимого массива\n\
            (6) Завершение программы\n");
        
        while (panel < 0  ||  panel > 6) {
            returned = safeScanfInt(&panel, 0);
            if (returned == 0) {
                free(arr);
                return 0;
            }
            if (panel < 0  ||  panel > 6) {
                printf("Введите число от 1 до 6!\n");
            }
        }
        
        switch(panel) {
        case 1:
            lencopy = 0;
            printf("Задайте длину массива\n");
            while (lencopy < 1) {
                returned = safeScanfInt(&lencopy, 1);
                if (returned == 0) {
                    free(arr);
                    return 0;
                }
                if (lencopy < 1) {
                    printf("Введите целое число не меньше 0!\n");
                }
            }
            returned = initializeArr (&arr, lencopy);
            if (returned == -1) {
                free(arr);
                return 0;
            }
            else if (returned == 1) {
                len = lencopy;
            }
            outputArr (arr, len);
            break;
        
        case 2:
            printf("Введите добавляемый элемент\n");
            returned = safeScanfDouble (&elem);
            if (returned == 0) {
                free(arr);
                return 0;
            }
            printf("Введите индекс добавления\n");
            while (ind < 0) {
                returned = safeScanfInt (&ind, 22);
                if (returned == 0) {
                    free(arr);
                    return 0;
                }
                if (ind < 0) {
                    printf("Введите целое число не меньше 0!\n");
                }
            }
            if (ind >= len) {
                ind = len - 1 + 1; // -1, т.к. индекса len нет, а +1, т.к. в этой ф.-и массив расширится
            }
            
            insertElem (&arr, &len, elem, ind);
            outputArr (arr, len);
            break;
        
        case 3:
            if (len == 0) {
                printf("Массив не проинициализирован - удалять нечего.\n");
                break;
            }
            printf("Введите индекс удаления\n");
            while (ind < 0  ||  ind >= len) {
                returned = safeScanfInt (&ind, 22);
                if (returned == 0) {
                    free(arr);
                    return 0;
                }
                if (ind < 0  ||  ind >= len) {
                    printf("Введите целое число не меньше 0 и меньше длины массива!\n");
                }
            }
            
            removeElem (&arr, &len, ind);
            outputArr (arr, len);
            break;
        case 4:
            individualTask (&arr, &len);
            outputArr (arr, len);
            break;
        case 5:
            outputArr (arr, len);
            break;
        case 6:
            printf("Завершение программы.\n");
            free(arr);
            return 0;
        }
    }
    
    return 0;
}

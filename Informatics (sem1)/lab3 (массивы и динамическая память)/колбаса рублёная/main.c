#include <stdio.h>
#include <stdlib.h>
#include "individualTask.h"
#include "initializeArr.h"
#include "insertElem.h"
#include "intFlComp.h"
#include "outputArr.h"
#include "removeElem.h"
#include "safeScanfDouble.h"
#include "safeScanfInt.h"

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

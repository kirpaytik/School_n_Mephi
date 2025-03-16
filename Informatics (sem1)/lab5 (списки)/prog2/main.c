#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "other.h"

int main()
{
    List *list = NULL;
    int panel, len, amm;
    int fl=1, returned, i;
    int pS1, pS2, pS3;
    clock_t start, end;
    double time_used;
    while (fl == 1) {
        printf("Выберите одну из опций:\n\
            (1) Генерация списка\n\
            (2) Вывод списка\n\
            (3) Сортировка списка\n\
            (4) Генерация + сортировка множества списков\n\
            (5) Завершение программы\n");

        panel = 0;
        while (panel < 1  ||  panel > 5) {
            printf("Введите число от 1 до 5!\n");
            returned = safeScanfInt(&panel);
            if (returned == 0) {
                fl = 0;
                endOfProgram(list);
                return 0;
            }
        }

        switch(panel) {
        case 1: // генерация списка
            printf("Введите длину списка\n");
            len = 0;
            while (len < 1) {
                printf("Введите число большее нуля!\n");
                returned = safeScanfInt(&len);
                if (returned == 0) {
                    fl = 0;
                    endOfProgram(list);
                    return 0;
                }
            }

            returned = initializeList(&list, len);
            if (returned == 0) {
                fl = 0;
                endOfProgram(list);
                return 0;
            }

            printf("Список создан\n");
            outputList(list);
            break;

        case 2: // вывод списка
            outputList(list);
            break;

        case 3: // сортировка списка
            returned = sortingList(list);
            if (returned == 0) {
                fl = 0;
                endOfProgram(list);
                return 0;
            }

            printf("Список отсортирован\n");
            outputList(list);
            break;

        case 4: // генерация + сортировка списков
            printf("Задайте длину списков - целое число >0\n\
                или 0, чтобы создавать списки (одинаковой) рандомной длины\n");
            len = -1;
            while (len < 0) {
                printf("Введите число большее -1!\n");
                returned = safeScanfInt(&len);
                if (returned == 0) {
                    fl = 0;
                    endOfProgram(list);
                    return 0;
                }
            }

            printf("Задайте количество списков - целое число >0\n\
                или 0, чтобы создать рандомное количество списков\n");
            amm = -1;
            while (amm < 0) {
                printf("Введите число большее -1!\n");
                returned = safeScanfInt(&amm);
                if (returned == 0) {
                    fl = 0;
                    endOfProgram(list);
                    return 0;
                }
            }
            if (amm == 0) {
                srand(clock());
                amm = rand() % 1000 + 1;
            }

            printf("Выберите алгоритм сортировки:\n\
                        (1) Сортировка расчёской (Comb sort)\n\
                        (2) Пирамидальная сортировка (Heap sort)\n\
                        (3) Быстрая сортировка (qsort)\n");
            pS1 = -1;
            while (pS1 < 1 || pS1 > 3) {
                printf("Введите целое число от 1 до 3!\n");
                returned = safeScanfInt(&pS1);
                if (returned == 0) {
                    return 0;
                }
            }

            printf("Выберите поле структуры, по которому будем сортировать:\n\
                (1) Адрес\n\
                (2) Кадастровый номер\n\
                (3) Площадь\n");
            pS2 = -1;
            while (pS2 < 1 || pS2 > 3) {
                printf("Введите целое число от 1 до 3!\n");
                returned = safeScanfInt(&pS2);
                if (returned == 0) {
                    return 0;
                }
            }

            printf("Выберите направление сортировки (возрастание/убывание:\n\
                (1) Возрастание\n\
                (2) Убывание\n");
            pS3 = -1;
            while (pS3 < 1 || pS3 > 2) {
                printf("Введите целое число от 1 до 2!\n");
                returned = safeScanfInt(&pS3);
                if (returned == 0) {
                    return 0;
                }
            }

            time_used = 0;
            for (i = 0; i < amm; i++) {
                returned = initializeList(&list, len);
                if (returned == 0) {
                    fl = 0;
                    endOfProgram(list);
                    return 0;
                }
                
                switch(pS1) {
                case 1:
                    start = clock();
                    combSort(list, pS2, pS3);
                    end = clock();
                    break;
                case 2:
                    start = clock();
                    heapSort(list, pS2, pS3);
                    end = clock();
                    break;
                case 3:
                    int lenlist = lenList(list);
                    start = clock();
                    quickSort(list, 0, lenlist-1, pS2, pS3);
                    end = clock();
                    break;
                }
                time_used += (double)(end - start) / CLOCKS_PER_SEC;
            }
            printf("На сортировку %d массивов затрачено %lf секунд\n", amm, time_used);
            if (len > 0 && amm > 1) {
                printf("В среднем - %lf секунд\n", time_used / (double)amm);
            }

            break;

        case 5: // завершение программы
            fl = 0;
            endOfProgram(list);
            return 0;
        }
    }

    // перебирает все элементы и каждый free(), включая поля элемента, а затем и сам list
    endOfProgram(list); // с принтом "Завершение программы\n"
    return 0;
}

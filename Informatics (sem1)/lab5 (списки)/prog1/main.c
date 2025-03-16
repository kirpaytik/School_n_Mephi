#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "other.h"

int main()
{
    List *list = (List*) malloc(sizeof(List));
    if (list == NULL) {
        printf("Не найдено свободной памяти\n");
        return 0;
    }
    list->head = NULL;

    int fl = 1;
    int panel;
    int pS1, pS2, pS3; // panelSort, три выбора там
    int returned;
    while (fl == 1) {
        printf("Выберите одну из опций:\n\
            (1) Ввод списка\n\
            (2) Вывод списка\n\
            (3) Сортировка списка\n\
            (4) Завершение программы\n");

        panel = 0;
        while (panel < 1  ||  panel > 4) {
            printf("Введите число от 1 до 4!\n");
            returned = safeScanfInt(&panel);
            if (returned == 0) {
                fl = 0;
                endOfProgram(list);
                return 0;
            }
        }

        switch(panel) {
        case 1: // ввод списка
            returned = initializeList(list);
            if (returned == 0) {
                fl = 0;
                endOfProgram(list);
                return 0;
            }

            printf("Список создан\n");
            returned = outputList(list);
            if (returned == 0) {
                fl = 0;
                endOfProgram(list);
                return 0;
            }
            break;

        case 2: // вывод списка
            returned = outputList(list);
            if (returned == 0) {
                fl = 0;
                endOfProgram(list);
                return 0;
            }
            break;

        case 3: // сортировка списка
            printf("Выберите алгоритм сортировки:\n\
                (1) Сортировка расчёской (Comb sort)\n\
                (2) Пирамидальная сортировка (Heap sort)\n\
                (3) Быстрая сортировка (qsort)\n");
            pS1 = -1;
            while (pS1 < 1 || pS1 > 3) {
                printf("Введите целое число от 1 до 3!\n");
                returned = safeScanfInt(&pS1);
                if (returned == 0) {
                    fl = 0;
                    endOfProgram(list);
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
                    fl = 0;
                    endOfProgram(list);
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
                    fl = 0;
                    endOfProgram(list);
                    return 0;
                }
            }

            switch(pS1) {
            case 1:
                combSort(list, pS2, pS3);
                break;
            case 2:
                heapSort(list, pS2, pS3);
                break;
            case 3:
                int lenlist = lenList(list);
                quickSort(list, 0, lenlist-1, pS2, pS3);
                break;
            }
            printf("Список отсортирован\n");
            returned = outputList(list);
            if (returned == 0) {
                fl = 0;
                endOfProgram(list);
                return 0;
            }
            break;

        case 4: // завершение программы
            fl = 0;
            endOfProgram(list);
            return 0;
        }
    }

    // перебирает все элементы и каждый free(), включая поля элемента, а затем и сам list
    endOfProgram(list); // с принтом "Завершение программы\n"
    return 0;
}

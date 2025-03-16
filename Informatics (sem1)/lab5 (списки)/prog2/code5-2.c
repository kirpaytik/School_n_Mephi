#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Item {
    char *adr, *num;
    double sqr;
    struct Item *next;
} Item;

typedef struct List {
    Item *head;
} List;



// вспомогательные для ввода

// вернёт 0 только в случае EOF, в остальных невалидных случаях запросит вновь
int safeScanfInt (int *target);

// для списков
int initializeList (List **list, int length);

void outputList (List *list);

int lenList (List *list);
// подгоняет *ptr на indx индекс
void ptrToIndx (List *list, Item **ptr, int indx);

// сортировки

// считывает всё для сортировки (вид, atr, dir) и вызывает нужное
int sortingList (List *list);

void combSort (List *list, int atr, int dir);

// правда, если дерево сверху вниз, то наоборот heapRecUp, просто корень же сверху, ну..
// prev2 - эл., который сравниваем с предком, prev1 - предок
void heapRecDown (List *list, Item *prev1, Item *prev2, int indx, int atr, int dir);
// правда, если дерево сверху вниз, то наоборот heapRecDown, просто корень же сверху, ну..
// parent - эл., который мы сравниваем с его листьями, prevPar - его prev (не предок, а prev)
// indx - индекс парента, last - индекс последнего элемента в оставшейся куче (т.к мы из кучи исключаем эл-ты)
void heapRecUp (List *list, Item *prevPar, Item *parent, int indx, int last, int atr, int dir);

void heapBuild (List *list, int atr, int dir);
void heapSort (List *list, int atr, int dir);

void quickSort (List *list, int left, int right, int atr, int dir);
int partition (List *list, int left, int right, int atr, int dir);

// Возвращает 1, если надо поменять в зав. от atr и dir, иначе - 0
int compareList (Item *item1, Item *item2, int atr, int dir);

// на самом деле, думаю, можно было бы в самих свапах сделать проверку на то, что элементы рядом
// хотя там из-за этой особенности и менять указатели надо было по-особенному, так что от ифок так не избавиться
void swap (Item *prev1, Item *prev2);
void swapNeghbours (Item *prev1);
void swapHead (List *list, Item *prev2);
void swapHeadNeghbours (List *list);

// фришки
void endOfProgram (List *list);



void freeList(List *list)
{
    if (list == NULL) {
        return;
    }
    Item *ptr = list->head;
    Item *next;
    while (ptr != NULL) {
            next = ptr->next;
            free(ptr->adr);
            free(ptr->num);
            free(ptr);
            ptr = next;
    }

    free(list);
}

void endOfProgram (List *list)
{
        freeList(list);
        printf("Завершение программы\n");
}

int safeScanfInt (int *target)
{
    int guard;
    int flag = 1;
    while (flag == 1) {
        guard = scanf("%d",target);
        scanf("%*[^\n]");
        scanf("%*c");
        if (guard == EOF) {
            return 0;
        }
        if (guard < 1) {
            printf("Введите целое число!\n");
            continue;
        }
        flag = 0;
    }
    return 1;
}



int initializeList (List **list, int length)
{
    // т.е пользователь вместо ввода длины попросил её сгенерировать
    if (length == 0) {
        srand(clock());
        length = (rand() % 1000) + 1;
    }
    if (list != NULL) {
        freeList(*list);
    }
    *list = (List*) malloc(length*sizeof(List));
    if (*list == NULL) {
        printf("Не найдено свободной памяти\n");
        return 0;
    }
    Item *ptr, *prev;
    int adrlen;
    srand(clock());
    for (int i = 0; i < length; i++) {
        ptr = (Item*)malloc(sizeof(Item));
        if (ptr == NULL) {
            printf("Не найдено свободной памяти\n");
            return 0;
        }
        adrlen = rand() % 100 + 10;
        ptr->adr = (char*)malloc((adrlen + 1) * sizeof(char));
        if (ptr->adr == NULL) {
            printf("Не найдено свободной памяти\n");
            return 0;
        }
        ptr->adr[adrlen] = '\0';
        for (int j = 0; j < adrlen; j++) {
            ptr->adr[j] = ('A' + (rand() % 26)) + (32 * (rand() % 2));
        }
        ptr->num = (char*)malloc((11+1) * sizeof(char));
        if (ptr->num == NULL) {
            printf("Не найдено свободной памяти\n");
            return 0;
        }
        ptr->num[11] = '\0';
        for (int j = 0; j < 11; j++) {
            if (j == 2 || j == 5 || j == 8) {
                ptr->num[j] = ':';
                continue;
            }
            if (j == 3 || j == 4) {
                ptr->num[j] = ('A' + (rand() % 26)) + (32 * (rand() % 2));
                continue;
            }
            if (j == 6 || j == 7) {
                ptr->num[j] = '0';
                continue;
            }
            ptr->num[j] = '0' + rand() % 10;
        }
        ptr->sqr = (double)rand() / RAND_MAX * 1000 + 0.5;
        ptr->next = NULL;
        if (i == 0) {
            (*list)->head = ptr;
            prev = ptr;
        }
        else {
            prev->next = ptr;
            prev = ptr;
        }
    }

    return 1; // всё ок
}

void outputList (List *list)
{
    Item *ptr = list->head;
    if (ptr == NULL) {
        printf("Список пуст!\n");
        return;
    }

    printf("Вывод последнего созданного списка, в каждой строке новый элемент\n");
    while (ptr != NULL) {
        printf("%s   %s   %lf\n", ptr->adr, ptr->num, ptr->sqr);
        ptr = ptr->next;
    }
}

int lenList (List *list)
{
    int len = 0;
    Item *ptr = list->head;
    while (ptr != NULL) {
        len++;
        ptr = ptr->next;
    }

    return len;
}

void swap (Item *prev1, Item *prev2)
{
    Item *temp;
    Item *ptr1 = prev1->next;
    Item *ptr2 = prev2->next;

    temp = ptr2->next;
    ptr2->next = ptr1->next;
    ptr1->next = temp;
    prev1->next = ptr2;
    prev2->next = ptr1;
}

void swapNeghbours (Item *prev1)
{
    Item *ptr1 = prev1->next;
    Item *ptr2 = ptr1->next;

    ptr1->next = ptr2->next;
    ptr2->next = ptr1;
    prev1->next = ptr2;
}

void swapHead (List *list, Item *prev2)
{
    Item *temp;
    Item *ptr1 = list->head;
    Item *ptr2 = prev2->next;

    temp = ptr2->next;
    ptr2->next = ptr1->next;
    ptr1->next = temp;
    list->head = ptr2;
    prev2->next = ptr1;
}

void swapHeadNeghbours (List *list)
{
    Item *ptr1 = list->head;
    Item *ptr2 = ptr1->next;

    ptr1->next = ptr2->next;
    ptr2->next = ptr1;
    list->head = ptr2;
}

void ptrToIndx (List *list, Item **ptr, int indx)
{
    *ptr = list->head;
    int i;
    for (i = 0; i < indx; i++) {
        *ptr = (*ptr)->next;
    }
}

int compareList (Item *item1, Item *item2, int atr, int dir)
{
    int comp;
    switch (atr) {
        case 1: // адрес
            comp = strcmp(item1->adr, item2->adr);
            break;

        case 2: // номер
            comp = strcmp(item1->num, item2->num);
            break;

        case 3: // площадь
            comp = item1->sqr - item2->sqr;
            break;
    }
    // comp < 0 => знак <, т.е возрастание. dir = 1 - возрастание.
    if ((comp < 0 && dir == 2) || (comp > 0 && dir == 1)) {
        return 1;
    }
    return 0;
}

void combSort (List *list, int atr, int dir)
{
    double factor = 1.25;
    int len = lenList(list);

    int step = len - 1;
    int i;
    Item *ptr1, *prev1, *prev2;
    while (step >= 1) {
        prev1 = NULL;
        ptr1 = list->head;
        ptrToIndx(list, &prev2, step-1);
        for (i = 0; i+step < len; i++) {
            if (compareList(ptr1, prev2->next, atr, dir)) {
                if (step == 1) { // если элементы соседние, то swap работает иначе
                    if (prev1 == NULL) {
                        swapHeadNeghbours(list);
                    }
                    else {
                        swapNeghbours(prev1);
                    }
                }
                else {
                    if (prev1 == NULL) {
                        swapHead(list, prev2);
                    }
                    else {
                        swap(prev1, prev2);
                    }
                }
            }
            if (prev1 == NULL)
                {prev1 = list->head;}
            else
                {prev1 = prev1->next;}
            ptr1 = prev1->next;
            if (step == 1) {prev2 = ptr1;} // потому что если они рядом, то при swap prev2 уедет, но если они рядом, то prev2=ptr1 - КОСТЫЛЬ!!!
            // легче было бы просто использовать на каждом шаге фора ptrToIndx, но это долго ведь
            else {prev2 = prev2->next;}
        }//for
        step /= factor;
    }//while
}
// правда, если дерево сверху вниз, то наоборот heapRecUp, просто корень же сверху, ну..
void heapRecDown (List *list, Item *prev1, Item *prev2, int indx, int atr, int dir)
{
    // if (indx == 0) {
    //     return;
    // } // не нужно, т.к. отсюда приходим только из 1 или 2, которые рассмотрены
    if (indx == 1) {
        if (compareList(list->head, list->head->next, atr, dir)) {
            swapHeadNeghbours(list);
        }
        return;
    }
    if (indx == 2) {
        if (compareList(list->head, list->head->next->next, atr, dir)) {
            swapHead(list, list->head->next); // надо дать prev, так что даю ->next, а не ->next->next
        }
        return;
    }

    if (compareList(prev1->next, prev2->next, atr, dir)) {
        swap(prev1, prev2);

        indx = (indx - 1) / 2; // новый индекс на ptr2
        prev2 = prev1;
        ptrToIndx(list, &prev1, (indx-1)/2 - 1);

        heapRecDown(list, prev1, prev2, indx, atr, dir);
    }
}

void heapBuild (List *list, int atr, int dir)
{
    int len = lenList(list);
    Item *prev1, *prev2;
    int i, j=0; // i - индекс last эл., j - его предок
    prev1 = NULL;
    prev2 = list->head;
    for (i = 1; i < len; i++) { // от i=1, т.к пирамида из 1 эл. - всегда пир. В.
        if (i == 2) {
            prev2 = list->head->next; // т.к. при i=1 после swap уезжает как раз prev2 - КОСТЫЛЬ!!!, как и в combsort
        }
        if (j == 1) {
            prev1 = list->head; // т.к. он тоже мог уехать - костыль
        }
        if (j < (i-1)/2) {
            j++;
            if (prev1 == NULL) {
                prev1 = list->head;
            }
            else {
                prev1 = prev1->next;
            }
        }
        heapRecDown(list, prev1, prev2, i, atr, 3 - dir); // 3 - dir, т.к. пирамида строится с монот. наоборот
        prev2 = prev2->next;
    }
}
// правда, если дерево сверху вниз, то наоборот heapRecDown, просто корень же сверху, ну..
void heapRecUp (List *list, Item *prevPar, Item *parent, int indx, int last, int atr, int dir)
{
    if (last == 0) {
        return; // потому что уже не с кем сравнивать
    }
    if (indx == 0) {
        Item *ptr1 = list->head->next;
        Item *ptr2 = ptr1->next;
        if (last == 1) {
            ptr2 = NULL; // потому что ptr2 уже вышел из кучи, но ptr1 - ещё нет
        }

        if (compareList(list->head, ptr1, atr, dir)) {
            if (ptr2 != NULL && compareList(ptr1, ptr2, atr, dir)) {
                swapHead(list, ptr1); // т.к нужен prev
                heapRecUp(list, list->head->next, list->head->next->next, 2, last, atr, dir);
            }
            else {
                swapHeadNeghbours(list);
                heapRecUp(list, list->head, list->head->next, 1, last, atr, dir);
            }
        }
        else if (ptr2 != NULL && compareList(list->head, ptr2, atr, dir)) {
            swapHead(list, ptr1); // т.к нужен prev
            heapRecUp(list, list->head->next, list->head->next->next, 2, last, atr, dir);
        }
        return;
    }

    int len = lenList(list);
    if (indx > len/2) {
        return; // потому что у parent нету листьев
    }

    if (2*indx+1 > last) {
        return; // т.к тогда ptr1 - элемент, уже исключённый из кучи
    }

    Item *prev1, *ptr1, *ptr2;
    ptrToIndx(list, &prev1, 2*indx+1 - 1);
    ptr1 = prev1->next;
    ptr2 = ptr1->next;

    if (2*indx+2 > last) {
        ptr2 = NULL; // т.к тогда ptr2 - элемент, уже исключённый из кучи, но ptr1 - нет
    }

    if (compareList(parent, ptr1, atr, dir)) {
        if (ptr2 != NULL && compareList(ptr1, ptr2, atr, dir)) {
            swap(prevPar, ptr1); // ptr1, т.к нужен prev
            heapRecUp(list, ptr1, ptr1->next, 2*indx+2, last, atr, dir);
        }
        else {
            swap(prevPar, prev1);
            heapRecUp(list, prev1, prev1->next, 2*indx+1, last, atr, dir);
        }
    }
    else if (ptr2 != NULL && compareList(parent, ptr2, atr, dir)) {
        swap(prevPar, ptr1); // т.к нужен prev
        heapRecUp(list, ptr1, ptr1->next, 2*indx+2, last, atr, dir);
    }
}

void heapSort (List *list, int atr, int dir)
{
    heapBuild(list, atr, dir);

    int len = lenList(list);
    int i;
    // цикл до 0, т.к при i=0 уже единственный элемент из кучи исключается, и менять ничего не надо
    for (i = len-1; i > 0; i--) { // здесь вылезает n^2, которого можно избежать, если бы List был двусвяз.
        Item *prev2;
        ptrToIndx(list, &prev2, i-1); // если двусвяз., не пришлось бы эту строку каждый раз

        if (i > 1) {
            swapHead(list, prev2); // меняем корень с последним
        }
        else {
            swapHeadNeghbours(list);
        }
        heapRecUp(list, NULL, NULL, 0, i-1, atr, 3 - dir);
    }
}

int partition (List *list, int left, int right, int atr, int dir)
{
    int pivot = left;
    int i;
    Item *prevPiv, *prevI, *ptrLeft;
    ptrToIndx(list, &ptrLeft, left);
    if (left == 0) {
        prevPiv = NULL;
        prevI = list->head;
    }
    else {
        ptrToIndx(list, &prevPiv, left-1);
        prevI = prevPiv->next;
    }
    for (i = left+1; i < right+1; i++) {
        if (compareList(ptrLeft, prevI->next, atr, dir)) {
            pivot++; // т.е первый pivot=left+1
            if (prevPiv == NULL) {prevPiv = list->head;}
            else {prevPiv = prevPiv->next;}

            if (i == pivot) { // никогда нет i<pivot, т.к они оба от left+1, а i бежит каждую итерацию, в отличие от pivot
                prevI = prevI->next;
                continue; // т.к зачем свапать с самим собой
            }
            // i > pivot
            if (i - pivot == 1) {
                swapNeghbours(prevPiv);
                continue; // т.к prevI свапнулся, то его не надо двигать
            }
            swap(prevPiv, prevI);
        }
        prevI = prevI->next;
    }

    if (pivot == left) {
        return pivot; // если pivot не изменился, то свапать ничего и не надо, ведь эта часть уже была отсортирована
    }
    if (left == 0) {
        if (list->head == prevPiv) {
            swapHeadNeghbours(list);
        }
        else {
            swapHead(list, prevPiv);
        }
    }
    else {
        Item *prevLeft;
        ptrToIndx(list, &prevLeft, left - 1);
        if (prevLeft->next == prevPiv) {
            swapNeghbours(prevLeft);
        }
        else {
            swap(prevLeft, prevPiv);
        }
    }
    return pivot;
}

void quickSort (List *list, int left, int right, int atr, int dir)
{
    if (left >= right) {
        return;
    }

    int mid = partition(list, left, right, atr, dir);
    quickSort(list, left, mid-1, atr, dir);
    quickSort(list, mid+1, right, atr, dir);
}

int sortingList (List *list)
{
    int returned;
    printf("Выберите алгоритм сортировки:\n\
                (1) Сортировка расчёской (Comb sort)\n\
                (2) Пирамидальная сортировка (Heap sort)\n\
                (3) Быстрая сортировка (qsort)\n");
    int pS1 = -1; // pS - panelSort
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
    int pS2 = -1;
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
    int pS3 = -1;
    while (pS3 < 1 || pS3 > 2) {
        printf("Введите целое число от 1 до 2!\n");
        returned = safeScanfInt(&pS3);
        if (returned == 0) {
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
    return 1;
}



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

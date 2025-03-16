#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    char letter;
    struct Item *next;
} Item;

typedef struct List {
    Item *head;
} List;

int safeScanfInt (int *target);

int initializeLists (List ***list, int *ammLists);
void outputLists (List **lists, int ammLists);
void individualTask (List **lists, int ammLists);

void ptrToWordEnd (Item **pointer);
void prevToIndx (List *list, Item **prev, int indx);
int compareWords (Item *ptr1, Item *ptr2);
// пододвигает слово 2 к слову 1 (ставит 2 после 1)
void moveWord (List *list, Item *ptr1, Item *prev2);
void moveWordFromHead (List *list, Item *end1, Item *end2);
void moveLastWord (Item *end1, Item *prev2, Item *end2);
void moveLastWordFromHead (List *list, Item *end1, Item *end2);
// void swapWords (Item *prev1, Item *end1, Item *prev2, Item *end2);
// не хватает Head+Last+swap, но в таком случае всего 2 эл.,
// swap+Head, т.к. ничем не отличается от moveToHead,
// и swap+Last, т.к. ничем не отличается от swap
// но Last+Head нужен для пуша неодинак вперёд (точнее наоборот одинак назад)

void endOfProgram (List **lists, int ammLists);
void freeLists (List **lists, int ammLists);



void freeLists (List **lists, int ammLists)
{
    // ввести строку, завершить и ввести снова - ошибка - доделать
    if (lists == NULL) {
        return;
    }
    int i;
    Item *ptr, *next;
    for (i = 0; i < ammLists; i++) {
        if (lists[i] == NULL) {
            break;
        }
        ptr = (lists[i])->head;
        while (ptr != NULL) {
            next = ptr->next;
            free(ptr);
            ptr = next;
        }
        free(lists[i]);
    }
    free(lists);
    lists = NULL;
}

void endOfProgram (List **lists, int ammLists)
{
    if (lists != NULL) {
        freeLists(lists, ammLists);
    }
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

int initializeLists (List ***lists, int *ammLists)
{
    if (*lists != NULL) {
        freeLists(*lists, *ammLists);
    }
    *lists = NULL;
    *ammLists = 0;
    char c;
    int len = 0;
    Item *ptr = NULL, *prev = NULL;
    List *templist = NULL;
    List **tempLists = NULL;
    // f - для while, spaceflag - 1, если предыдущий символ - пробел
    // newstrflag - флаг новой строки
    int f = 1, spaceflag = 1, newstrflag = 1;
    printf("Введите первую строку\n");
    while (f > 0) {
        c = getchar();
        if (c == EOF) {
            clearerr(stdin);
            return 1;
        }
        if (c == '\n') {
            if (ptr->letter == ' ' || ptr->letter == '\t') {
                prev->next = NULL;
                free(ptr);
            }
            newstrflag = 1;
            printf("Введите %d-ю строку\n", (*ammLists)+1);
            continue;
        }
        if ((spaceflag == 1 || newstrflag == 1) && (c == ' ' || c == '\t')) {
            spaceflag = 1;
            // убираем много пробелов подряд
            continue;
        }
        if (c == ' ' || c == '\t') {
            spaceflag = 1;
        }
        else {
            spaceflag = 0;
        }
        prev = ptr;
        ptr = NULL;
        ptr = (Item*)malloc(sizeof(Item));
        if (ptr == NULL) {
            printf("Не найдено свободной памяти\n");
            return 0;
        }
        ptr->letter = c;
        ptr->next = NULL;
        if (newstrflag == 1) {
            newstrflag = 0;
            if (*lists == NULL) {
                *lists = (List**)malloc(sizeof(List*));
                if (*lists == NULL) {
                    free(ptr);
                    printf("Не найдено свободной памяти\n");
                    return 0;
                }
            }
            else {
                tempLists = NULL;
                tempLists = (List**)realloc(*lists, ((*ammLists) + 1)*sizeof(List*));
                if (tempLists == NULL) {
                    free(ptr);
                    printf("Не найдено свободной памяти\n");
                    return 0;
                }
                *lists = tempLists;
            }
            (*lists)[*ammLists] = NULL;
            (*lists)[*ammLists] = (List*)malloc(sizeof(List));
            if ((*lists)[*ammLists] == NULL) {
                free(ptr);
                printf("Не найдено свободной памяти\n");
                return 0;
            }
            (*lists)[*ammLists]->head = ptr;
            // prev = ptr; пишу не здесь для обработки пробелов перед '\n'
            (*ammLists)++;
            len = 1;
            continue;
        }
        // else if (newstrflag == 1)
        templist = NULL;
        templist = (List*)realloc((*lists)[(*ammLists) - 1], (len + 1)*sizeof(List));
        if (templist == NULL) {
            free(ptr);
            printf("Не найдено свободной памяти\n");
            return 0;
        }
        (*lists)[(*ammLists) - 1] = templist;
        prev->next = ptr;
        len++;
    }
}

void outputLists (List **lists, int ammLists)
{
    if (ammLists == 0) {
        printf("Список пуст!\n");
        return;
    }
    Item *ptr;
    int i;
    printf("Вывод строк\n");
    for (i = 0; i < ammLists; i++) {
        printf("%d-я строка:\n\"", i+1);
        ptr = lists[i]->head;
        while (ptr != NULL) {
            printf("%c", ptr->letter);
            ptr = ptr->next;
        }
        printf("\"\n");
    }
}

void ptrToWordEnd (Item **pointer)
{
    Item *prev = *pointer;
    Item *ptr = *pointer;
    while (ptr != NULL && ptr->letter != ' ' && ptr->letter != '\t') {
        prev = ptr;
        ptr = ptr->next;
    }
    *pointer = prev;
}

int compareWords (Item *ptr1, Item *ptr2)
{
    char mask1[27] = "00000000000000000000000000\0";
    char mask2[27] = "00000000000000000000000000\0";
    char c;
    while (ptr1->letter != ' ' && ptr1->letter != '\t') {
        c = ptr1->letter;
        if (c >= 'A' && c <= 'Z') {
            c += ('a' - 'A');
        }
        mask1[c - 'a'] = '1';
        ptr1 = ptr1->next;
    }
    while (ptr2 != NULL && ptr2->letter != ' ' && ptr2->letter != '\t') {
        c = ptr2->letter;
        if (c >= 'A' && c <= 'Z') {
            c += ('a' - 'A');
        }
        mask2[c - 'a'] = '1';
        ptr2 = ptr2->next;
    }
    if (strcmp(mask1, mask2) == 0) {
        return 1;
    }
    return 0;
}

void moveWord (List *list, Item *prev1, Item *prev2)
{
    Item *end1;
    if (prev1 == NULL) {
        end1 = list->head;
    }
    else {
        end1 = prev1->next;
    }
    ptrToWordEnd(&end1);
    Item *end2 = prev2->next;
    ptrToWordEnd(&end2);
    if (end2->next == NULL) {
        moveLastWord(end1, prev2, end2);
        return;
    }
    Item *temp1, *temp2;
    temp1 = end1->next->next;
    temp2 = end2->next->next;

    end1->next->next = prev2->next;
    end2->next->next = temp1;
    prev2->next = temp2;
}
void moveLastWord (Item *end1, Item *prev2, Item *end2)
{
    Item *prevP2 = end1;
    while (prevP2->next != prev2) {
        prevP2 = prevP2->next;
    }
    end2->next = end1->next;
    end1->next = prev2;
    prevP2->next = NULL;
}

void moveWordFromHead (List *list, Item *end1, Item *end2)
{
    Item *temp1, *temp2;
    temp1 = list->head;
    temp2 = end2->next->next;
    
    list->head = end1->next->next;
    end2->next->next = temp1;
    end1->next->next = temp2;
}

void moveLastWordFromHead (List *list, Item *end1, Item *end2)
{
    Item *temp1;
    temp1 = list->head;

    list->head = end1->next->next;
    end2->next = end1->next;
    end2->next->next = temp1;
    end1->next = NULL;
}

void prevToIndx (List *list, Item **prev, int indx)
{
    if (indx == 0) {
        *prev = NULL;
        return;
    }
    Item *ptr = list->head;
    int i;
    for (i = 0; i < indx; i++) {
        ptrToWordEnd(&ptr);
        ptr = ptr->next;
    }
    *prev = ptr;
}

void individualTask(List **lists, int ammLists)
{
    // ИНДЕКСЫ ПОСЛЕ МУВОВ МЕНЯЮТСЯЯЯЯЯЯ
    int i;
    Item *prev1, *ptr1, *end1, *prev2, *end2;
    Item *prev0, *end0;
    // было бы лучше хранить и работать с end1 и end2 здесь же,
    // чтобы в функциях compareWords() и swapWords()
    // не вызывать снова и снова ptrToWordEnd()
    int indx1, indx2;
    int indx0;
    int flag;
    for (i = 0; i < ammLists; i++) {
        prev1 = NULL;
        indx1 = 0;
        while (prev1 != NULL || indx1 == 0) {
            if (prev1 == NULL) {
                prev2 = (lists[i])->head;
            }
            else {
                prev2 = prev1->next;
            }
            ptrToWordEnd(&prev2);
            prev2 = prev2->next;
            indx2 = indx1 + 1;
            while (prev2 != NULL) {
                if (prev1 == NULL) {
                    ptr1 = (lists[i])->head;
                }
                else {
                    ptr1 = prev1->next;
                }
                if (compareWords(ptr1, prev2->next)) {
                    if (indx2 - indx1 == 1) {
                        // сдвиг prev1 и prev2 без мувов
                        if (prev1 == NULL) {
                            prev1 = (lists[i])->head;
                        }
                        else {
                            prev1 = prev1->next;
                        }
                        ptrToWordEnd(&prev1);
                        prev1 = prev1->next;
                        indx1++;
                        prev2 = prev2->next;
                        ptrToWordEnd(&prev2);
                        prev2 = prev2->next;
                        indx2++;
                        continue;
                    }
                    end2 = prev2->next;
                    ptrToWordEnd(&end2);
                    if (end2->next == NULL) {
                        end1 = ptr1;
                        ptrToWordEnd(&end1);
                        moveLastWord(end1, prev2, end2);
                        break; // т.к дальше нет слов для сравнения
                    }
                    moveWord(lists[i], prev1, prev2);
                    if (prev1 == NULL) {
                        prev1 = (lists[i])->head;
                    }
                    else {
                        prev1 = prev1->next;
                    }
                    ptrToWordEnd(&prev1);
                    prev1 = prev1->next;
                    indx1++;
                    indx2++;
                    // prev2 не двигаем, т.к после мува он сам "сдвинулся"
                    continue;
                } // if (compare(...))
                // т.к while (prev2 != NULL), то prev2 указ на пробел => сущ след слово
                prev2 = prev2->next;
                ptrToWordEnd(&prev2);
                prev2 = prev2->next;
                indx2++;
            } // while (prev2 != NULL)
            prev1 = prev1->next;
            ptrToWordEnd(&prev1);
            prev1 = prev1->next;
            indx1++;
        } // while (prev1 != NULL || indx == 0)
        // запоминаем последнего повторяющегося в prev0
        prev0 = NULL;
        indx0 = 0;
        prev1 = NULL;
        indx1 = 0;
        prev2 = (lists[i])->head;
        ptrToWordEnd(&prev2);
        prev2 = prev2->next;
        indx2 = 1;
        flag = 0;
        while (ptr2 != NULL) {
            if (prev1 == NULL) {
                ptr1 = (lists[i])->head;
            }
            else {
                ptr1 = prev1->next;
            }
            if (compareWords(ptr1, prev2->next)) {
                flag = 1;
            }
            else {
                if (flag == 1) {
                    flag = 0;
                    prev0 = prev1;
                    indx0 = indx1;
                }
            }
            //
            if (prev1 == NULL) {
                prev1 = (lists[i])->head;
            }
            else {
                prev1 = prev1->next;
            }
            ptrToWordEnd(&prev1);
            prev1 = prev1->next;
            indx1++;
            prev2 = prev2->next;
            ptrToWordEnd(&prev2);
            prev2 = prev2->next;
            indx2++;
        }
        if (flag == 1) {
            prev0 = prev1;
            indx0 = indx1;
        }
        // итого в prev0 последний повторённый
        end0 = prev0->next;
        ptrToWordEnd(end0);
        // проходим всех до него и выкидываем за него неповторки
        prev1 = NULL;
        indx1 = 0;
        prev2 = (lists[i])->head;
        ptrToWordEnd(&prev2);
        prev2 = prev2->next;
        indx2 = 1;
        flag = 0;
        while (indx2 < indx0) {
            if (prev1 == NULL) {
                ptr1 = (lists[i])->head;
            }
            else {
                ptr1 = prev1->next;
            }
            if (!compareWords(ptr1, prev2->next)) {
                if (flag == 0) {
                    flag = 1;
                    continue;
                }
                if (prev1 == NULL && end0->next == NULL) {
                    end1 = ptr1;
                    ptrToWordEnd(&end1);
                    moveLastWordFromHead(lists[i], end1, end0);
                    prevToIndx(lists[i], &prev0, indx0);
                    // continue? - доделать
                }
                if (prev1 == NULL) {
                    end1 = ptr1;
                    ptrToWordEnd(&end1);
                    moveWordFromHead(lists[i], end1, end2);
                    // continue?
                }
                if (end0->next == NULL) {
                    end1 = ptr1;
                    ptrToWordEnd(&end1);
                    moveLastWord(end1, prev0, end0);
                    // continue?
                }
                moveWord(lists[i], prev1, prev0);
            }
            else {
                flag = 0;
            }
        }
    } // for (i = 0; i < ammLists; i++)
}



int main()
{
    List **lists = NULL;
    int ammount = 0;
    int panel;
    int fl = 1, returned;
    while (fl == 1) {
        printf("Выберите одну из опций:\n\
            (1) Ввод строки\n\
            (2) Вывод строки\n\
            (3) Индивидуальное задание\n\
            (4) Завершение программы\n");
        panel = 0;
        while (panel < 1  ||  panel > 4) {
            printf("Введите число от 1 до 4!\n");
            returned = safeScanfInt(&panel);
            if (returned == 0) {
                fl = 0;
                endOfProgram(lists, ammount);
                return 0;
            }
        }
        switch(panel) {
        case 1: // ввод строки
            returned = initializeLists(&lists, &ammount);
            if (returned == 0) {
                endOfProgram(lists, ammount);
                return 0;
            }
            outputLists(lists, ammount);
            break;

        case 2: // вывод строки
            outputLists(lists, ammount);
            break;

        case 3: //  индивидуальное задание
            individualTask(lists, ammount);
            outputLists(lists, ammount);
            break;

        case 4:
            fl = 0;
            endOfProgram(lists, ammount);
            return 0;
        }
    }
    endOfProgram(lists, ammount);
    return 0;
}
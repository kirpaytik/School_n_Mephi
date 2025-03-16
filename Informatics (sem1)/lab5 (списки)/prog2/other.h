#ifndef OTHER_H
#define OTHER_H

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
void freeList (List *list);
void endOfProgram (List *list);

#endif

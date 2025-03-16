#ifndef TABLE_H
#define TABLE_H

typedef struct KeySpace {
    unsigned int key;
    int rel;
    char* info;
} KeySpace;

typedef struct Node {
	KeySpace data;
	struct Node* prev;
	struct Node* next;
} Node;

typedef struct Table Table;


// struct Table
int t_create(Table** dest);
void t_free(Table* table);
void t_print_console(Table* table);
void t_print_file(Table* table, FILE* file);

int t_insert(Table* table, KeySpace ks);
int t_find_lastrel(Table table, unsigned int key);
int t_delete(Table* table, unsigned int key, int rel);
int t_remove(Table* table, Node* node);
int t_find(Table* table, unsigned int key, int rel, Table* dest);


int t_is_empty(Table* table);

#ifdef USE_ITER

// struct Iterator
typedef struct Iter Iter;
int iter_create(Table* table, Iter** dest);
void iter_free(Iter* iter);
int iter_has_next(Iter* iter);
int iter_get_next(Iter* iter);
int iter_get_last(Iter* iter);
int iter_equals(Iter* iter1, Iter* iter2);

#endif

#endif

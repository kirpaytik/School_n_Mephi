#ifndef TABLELIB_H
#define TABLELIB_H

#define OK 0
#define ERR 1
#define NDef -1

typedef struct KeySpace {
	int key;
	char *info;
} KeySpace;

typedef struct Table {
	KeySpace *ks;
	int msize;
	int csize;
} Table;


Table create_table(int size);
void print_table(Table table);
void free_table(Table *table);

int find_key(Table table, int key);
KeySpace get_key(Table table, int key);
int put_key(Table *table, int key, char *info);
int del_key(Table *table, int key);

#endif

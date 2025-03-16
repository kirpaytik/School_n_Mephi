#ifndef TABLE_H
#define TABLE_H

// KeySpace и Table там
#include "mylib.h"


// struct Table
int t_create(Table** dest);
int t_set_size(Table* table, int msize);
void t_free(Table* table);
void t_print_console(Table* table);
void t_print_txtfile(Table* table, FILE* file);
void t_print_binfile(Table* table, FILE* file);

int t_insert(Table* table, KeySpace ks);
int t_delete(Table* table, unsigned int key);
int t_find(Table* table, unsigned int key, KeySpace* dest);
int t_clear(Table* table);

int t_is_empty(Table* table);
int t_get_newsize(int oldsize);
int isPrime(int num);
int t_get_msize(Table* table);
int t_get_csize(Table* table);

// hash.c
unsigned int hash1(unsigned int key, int msize);
unsigned int hash2(unsigned int key, int msize);

#endif

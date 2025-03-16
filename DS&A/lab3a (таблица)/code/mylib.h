#ifndef MYLIB_H
#define MYLIB_H

#include <stdio.h>

typedef struct Table Table;

// dialog.c
int dialogue(Table* table, Table* table2);
int dialog_menu(Table* table, Table* table2, int panel);
int dialog_fill(Table* table);
int dialog_fill_console(Table* table);
int dialog_fill_file(Table* table);
int dialog_insert_console(Table* table);
int dialog_insert_file(Table* table, FILE* file);
int dialog_delete(Table* table);
int dialog_find(Table* table, Table* table2);
int dialog_print(Table* table, Table* table2);


// input.c
int safeScanfInt(int* target);
int safeScanfUInt(unsigned int* target);
int safeFileScanfInt(int* target, FILE* file);
int safeFileScanfUInt(unsigned int* target, FILE* file);
int is_int_overflow(char s[13]);
int is_uint_overflow(char s[12]);
char* readline(char* output);
char* readFileLine(char* output, FILE* file);
int read_y_or_n(char* dest);


// job.c
int create_table(Table** dest);
void endofprog(Table* table1, Table* table2);

void job_print_console(Table* table);
void job_print_file(Table* table, FILE* file);
int job_insert(Table* table, unsigned int key, char* info);
int job_delete(Table* table, unsigned int key, int rel);
int job_clear(Table* table);
int job_find(Table* table, unsigned int key, int rel, Table* table2);

#endif

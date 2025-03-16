#ifndef MYLIB_H
#define MYLIB_H

#include <stdio.h>

typedef struct KeySpace {
	int busy;
    unsigned int key;
    unsigned int info;
} KeySpace;

typedef struct Table Table;

// dialog.c
int dialogue_start(Table* table);
int dialog_menu(Table* table);
int dialog_switch(Table* table, int panel);

int dialog_fill(Table* table);
int dialog_fill_console(Table* table);
int dialog_fill_file(Table* table, FILE* file, int mode);
int dialog_insert_console(Table* table);
int dialog_insert_file(Table* table, FILE* file, int mode);

int dialog_delete(Table* table);
int dialog_find(Table* table);
int dialog_print(Table* table);


// input.c
int scanfInt(int* target, FILE* file, int mode);
int scanfUInt(unsigned int* target, FILE* file, int mode);
int scanfConsoleInt(int* target);
int scanfConsoleUInt(unsigned int* target);
int scanfTxtFileInt(int* target, FILE* file);
int scanfTxtFileUInt(unsigned int* target, FILE* file);
int scanfBinFileInt(int* target, FILE* file);

int is_int_overflow(char s[13]);
int is_uint_overflow(char s[12]);

int readline(char* output, char** dest);
int remove_end_spaces(char** dest);

int read_y_or_n(char* dest);
int read_int_inrange(int* dest, int min, int max);


// job.c
int create_table(Table** dest);
void endofprog(Table* table1);

int job_set_size(Table* table, int msize, int force);
void job_print(Table* table, FILE* file, int mode);
int job_insert(Table* table, unsigned int key, int info);
int job_delete(Table* table, unsigned int key);
int job_clear(Table* table);
int job_find(Table* table, unsigned int key, KeySpace* dest);

#endif

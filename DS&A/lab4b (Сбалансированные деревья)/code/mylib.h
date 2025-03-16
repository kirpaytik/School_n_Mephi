#ifndef MYLIB_H
#define MYLIB_H

#include <stdio.h> // для FILE*
#include <stdbool.h>

typedef struct KeySpace {
    char* key;
    unsigned int info;
} KeySpace;

typedef struct Tree Tree;

// dialog.c
short dialogue_menu(Tree* tree);
short dialog_switch(Tree* tree, int panel);

short dialog_fill_file(Tree* tree);
short dialog_insert_multiple(Tree* tree);
short dialog_insert(Tree* tree);
short dialog_delete(Tree* tree);
short dialog_traversal(Tree* tree);
short dialog_print(Tree* tree);
short dialog_print_console(Tree* tree);
short dialog_print_txtfile(Tree* tree);
short dialog_print_graphviz(Tree* tree);
short dialog_find(Tree* tree, short mode);


short dialog_get_file(FILE** file, char filemode[3]);


// input.c
short scanfIntType(int* target, FILE* file, short mode);
short scanfUIntType(unsigned int* target, FILE* file, short mode);
short scanfConsoleInt(int* target);
short scanfConsoleUInt(unsigned int* target);
short scanfTxtFileInt(int* target, FILE* file);
short scanfTxtFileUInt(unsigned int* target, FILE* file);
short scanfBinFileInt(int* target, FILE* file);
short scanfBinFileUInt(unsigned int* target, FILE* file);

short is_int_overflow(char s[13]);
short is_uint_overflow(char s[12]);

short readline(char** dest, FILE* file, short mode, bool empty_rule);
short readConsoleLine(char** dest, bool empty_rule);
short readTxtFileLine(char** dest, FILE* file, bool empty_rule);
short remove_end_spaces(char** dest);

short read_y_or_n(char* dest);
short read_int_inrange(void* dest, short type, int min, int max);


// job.c
short create_tree(Tree** dest);
void endofprog(Tree* tree);
short start_program(Tree* tree);

short job_insert(Tree* tree, char* key, unsigned int info, unsigned int* previnfo);
short job_delete(Tree* tree, char* key);
void job_clear(Tree* tree);
void job_traversal(Tree* tree, char* key, short mode);
short job_print(Tree* tree, FILE* file, short mode);
short job_find(Tree* tree, char* key, short mode,
    char** foundkey, unsigned int* info);

#endif
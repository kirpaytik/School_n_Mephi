#ifndef DOPLIB_H
#define DOPLIB_H

#include <stdio.h>

typedef struct KeySpace {
        char* key;
        unsigned int info;
} KeySpace;

typedef struct Tree Tree;

short create_tree(Tree** dest);
void endofprog(Tree* tree);
short start_program(Tree* tree);

short dialog_get_file(FILE** file, char filemode[3]);

short readConsoleLine(char** dest);
short remove_end_spaces(char** dest);
short readTxtFileLine(char** dest, FILE* file);

short build_tree_fromTxt(FILE* file, Tree* tree);
short find_the_word(char* word, Tree* tree);

#endif

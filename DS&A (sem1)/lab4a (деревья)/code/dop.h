#ifndef DOPLIB_H
#define DOPLIB_H

#include <stdio.h> // для FILE*

typedef struct KeySpace {
    unsigned int key;
    char* info;
} KeySpace;

typedef struct Tree Tree;

short create_tree(Tree** dest);
void endofprog(Tree* tree);
short start_program(Tree* tree);

short job_collect(Tree* tree);
short dialog_get_file(FILE** file, char filemode[3]);

short scanfBinFileInt(unsigned int* target, FILE* file);
short readline(char** dest);
short remove_end_spaces(char** dest);

#endif

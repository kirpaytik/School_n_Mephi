#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dop.h"
#include "tree.h"

#define OK 0
#define BAD 1
#define END 2
#define PASS 3
#define MEMORY 4
#define TREE_EMPTY -2
#define TREE_NOTFOUND -1
#define TREE_DUPLICATE -1

#define CONSOLE_MODE 0
#define TXTFILE_MODE 1
#define BINFILE_MODE 2

#define NOFILE NULL

#define SHORT_TYPE 1
#define INT_TYPE 2
#define UINT_TYPE 3

#define EMPTYRULE_FALSE false
#define EMPTYRULE_TRUE true

short create_tree(Tree** dest)
{
        return t_create(dest);
}


void endofprog(Tree* tree)
{
        t_free(tree);
        free(tree);
}


short start_program(Tree* tree)
{
        FILE* file;
        short checker = dialog_get_file(&file, "r\0\0");
        if (checker) return BAD;

        checker = build_tree_fromTxt(file, tree);
        fclose(file);
        if (checker) return BAD;

        char* word;
        printf("Input a word to find\n");
        short guard = readConsoleLine(&word);
        if (!guard) return BAD;

        checker = find_the_word(word, tree);
        free(word);
        if (checker) return BAD;
        return OK;
}


short build_tree_fromTxt(FILE* file, Tree* tree)
{
        char* line;
        char* word;
        short guard = readTxtFileLine(&line, file);
        unsigned int num = 1;
        unsigned int temp;
        short checker;
        while (guard != EOF) {
                word = strtok(line, " ");
                while (word) {
                        KeySpace ks = (KeySpace){NULL, num};
                        ks.key = (char*)malloc(sizeof(char) * (strlen(word) + 1));
                        if (!ks.key) return MEMORY;
                        strcpy(ks.key, word);
                        checker = t_insert(tree, ks, &temp);
                        if (checker == -1) {
                                ks.info = temp;
                                checker = t_insert(tree, ks, &temp);
                        }
                        if (checker && checker != -1) {free(line); return checker;}

                        word = strtok(NULL, " ");
                }
                free(line);
                guard = readTxtFileLine(&line, file);
                num++;
        }
        return OK;
}


short find_the_word(char* word, Tree* tree)
{
        Node* found;
        unsigned int temp;
        short checker = t_find(tree, word, &found, &temp);
        if (checker) printf("The word %s was not found!\n", word);
        else printf("The first accurance of word %s is found on line #%u\n", word, found->info);
        return OK;
}


short dialog_get_file(FILE** file, char filemode[3])
{
        short guard;
        char* filename;
        printf("Name of file to open:\n");
        guard = readConsoleLine(&filename);
        if (guard == EOF) {
                printf("Ctrl+D detected. Ending the program.\n");
                return END;
        }
        if (!guard) {
                printf("Inputting a string error\n");
                return BAD;
        }
        *file = fopen(filename, filemode);
        free(filename);
        if (!*file) {
                printf("File opening error!\n");
                return PASS;
        }
        return OK;
}


short readConsoleLine(char** dest)
{
        char* ptr = (char*)malloc(1);
        if (ptr == NULL) return 0;
        *ptr = '\0';
        char buf[81];
        short n=0;
        int len=0;
        char* temp = NULL;

        printf(">>> ");
        scanf("%*[^\n0-9a-zA-Z]");
        do {
                n = scanf("%80[^\n]", buf);
                if (n == EOF) {
                        free(ptr);
                        return n;
                }
                if (n == 0) {
                        scanf("%*c");
                        break;
                }
                len += strlen(buf);
                temp = (char*)realloc(ptr, sizeof(char) * (len + 1));
                if (temp == NULL) {
                        free(ptr);
                        return 0;
                }
                ptr = temp;
                strcat(ptr, buf);
        } while (n >= 0);

        remove_end_spaces(&ptr);
        *dest = ptr;
        return 1;
}


short readTxtFileLine(char** dest, FILE* file)
{
        char* ptr = (char*)malloc(1);
        if (ptr == NULL) return 0;
        *ptr = '\0';
        char buf[81];
        short n=0;
        int len=0;
        char* temp = NULL;

        fscanf(file, "%*[^\n0-9a-zA-Z]");
        do {
                n = fscanf(file, "%80[^\n]", buf);
                if (n == EOF) {
                        free(ptr);
                        return n;
                }
                if (n == 0) {
                        fscanf(file, "%*c");
                        break;
                }
                len += strlen(buf);
                temp = (char*)realloc(ptr, sizeof(char) * (len + 1));
                if (temp == NULL) {
                        free(ptr);
                        return 0;
                }
                ptr = temp;
                strcat(ptr, buf);
        } while (n >= 0);

        remove_end_spaces(&ptr);
        *dest = ptr;
        return 1;
}


short remove_end_spaces(char** dest)
{
        int i = strlen(*dest) - 1;
        while (i > -1 && ((*dest)[i] == ' ' || (*dest)[i] == '\t')) {
                i--;
        }
        (*dest)[i + 1] = '\0';
        char* temp = (char*)realloc(*dest, sizeof(char) * (i + 2));
        if (!temp) return 0;

        *dest = temp;
        return 1;
}

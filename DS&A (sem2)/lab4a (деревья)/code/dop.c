#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dop.h"
#include "tree.h"

#define OK 0
#define BAD 1
#define END 2
#define PASS 3

#define CONSOLE_MODE 0
#define TXTFILE_MODE 1
#define BINFILE_MODE 2


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
	short checker = job_collect(tree);
	if (checker)
		return checker;
	t_count(tree);
	return OK;
}


short job_collect(Tree* tree)
{
	short checker;
	FILE* file;
	checker = dialog_get_file(&file, "rb\0");
	if (checker)
		return checker;

	short guard = 1;
	unsigned int num;
	char* info;
	while (guard != EOF) {
		guard = scanfBinFileInt(&num, file);
		if (guard == EOF)
			break;
		info = (char*)malloc(sizeof(char));
		*info = '\0';
		KeySpace ks = (KeySpace){num, info};
		checker = t_insert(tree, ks);
		if (checker) {
			fclose(file);
			return BAD;
		}
	}
	fclose(file);
	return OK;
}


short dialog_get_file(FILE** file, char filemode[3])
{
	short guard;
	char* filename;
	printf("Name of file to open:\n");
	guard = readline(&filename);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
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


short scanfBinFileInt(unsigned int* target, FILE* file)
{
	unsigned int num;
	fread(&num, sizeof(int), 1, file);
	if (ferror(file))
		return 0;
	if (feof(file))
		return EOF;

	*target = num;
	return 1;
}


short readline(char** dest)
{
    char *ptr = (char*)malloc(1);
    if (ptr == NULL) {
        printf("Не найдено свободной памяти\n");
        return 0;
    }
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
        }
        else {
            len += strlen(buf);
            temp = (char*)realloc(ptr, (len+1)*sizeof(char));
            if (temp == NULL) {
            	printf("Недостаточно свободной памяти!\n");
                free(ptr);
                return 0;
            }
            ptr = temp;
            strcat(ptr, buf);
        }
    } while (n > 0);

    remove_end_spaces(&ptr); // heres no guard for allocation. no need tho i think
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
	char* temp = (char*)realloc(*dest, (i + 2) * sizeof(char));
	if (temp == NULL) {
		printf("Memory allocation error!\n");
		return 0;
	}
	*dest = temp;
	return 1;
}

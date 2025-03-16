#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "mylib.h"

#define CONSOLE_MODE 0
#define TXTFILE_MODE 1
#define BINFILE_MODE 2

#define SHORT_TYPE 1
#define INT_TYPE 2
#define UINT_TYPE 3


short scanfIntType(int* target, FILE* file, short mode)
{
	short guard;
	switch (mode) {
	case CONSOLE_MODE:
		guard = scanfConsoleInt(target);
		break;
	case TXTFILE_MODE:
		guard = scanfTxtFileInt(target, file);
		break;
	case BINFILE_MODE:
		guard = scanfBinFileInt(target, file);
		break;
	}
	return guard;
}


short scanfUIntType(unsigned int* target, FILE* file, short mode)
{
	short guard;
	switch (mode) {
	case CONSOLE_MODE:
		guard = scanfConsoleUInt(target);
		break;
	case TXTFILE_MODE:
		guard = scanfTxtFileUInt(target, file);
		break;
	case BINFILE_MODE:
		// отдельная функция для UINT здесь даже не нужна
		int num;
		guard = scanfBinFileInt(&num, file);
		if (guard == 1)
			*target = num;
		break;
	}
	return guard;
}


short scanfConsoleInt(int* target)
{
	short guard;
	char buf[13];
	// 13, т.к INT_MAX содержит 10 цифр + '-' + один знак для оценки переполнения + '\0'
	buf[12] = '\0';
	int num;
	while (1)
	{
		printf(">>> ");
		guard = scanf(" %12[^ \t\n]", buf);
		if (guard == EOF) {
			return guard;
		}
		guard = sscanf(buf, "%d", &num);
		if (guard != 1) {
			scanf("%*[^\n]%*c");
			printf("Введено не целое число! Введено: %s\n", buf);
			continue;
		}
		if (is_int_overflow(buf)) {
		    scanf("%*[^\n]%*c");
		    printf("Слишком большое число! Введено: %s\n", buf);
		    continue;
		}
		break;
	}
	scanf("%*c");
	*target = num;
	return 1;
}


short scanfConsoleUInt(unsigned int* target)
{
	short guard;
	char buf[12];
	// 12, т.к UINT_MAX содержит 10 цифр + '-' + один знак для оценки переполнения + '\0'
	buf[11] = '\0';
	unsigned int num;
	while (1)
	{
		printf(">>> ");
		guard = scanf(" %11[^ \t\n]", buf);
		if (guard == EOF) {
			return guard;
		}
		guard = sscanf(buf, "%u", &num);
		if (guard != 1) {
			scanf("%*[^\n]%*c");
			printf("Введено не целое число! Введено: %s\n", buf);
			continue;
		}
		if (buf[0] == '-') {
			scanf("%*[^\n]%*c");
			printf("Введено отрицательное число! Введено: %s\n", buf);
			continue;
		}
		if (is_uint_overflow(buf)) {
		    scanf("%*[^\n]%*c");
		    printf("Слишком большое число! Введено: %s\n", buf);
		    continue;
		}
		break;
	}
	scanf("%*c");
	*target = num;
	return 1;
}


short scanfTxtFileInt(int* target, FILE* file)
{
	short guard;
	char buf[13];
	// 13, т.к INT_MAX содержит 10 цифр + '-' + один знак для оценки переполнения + '\0'
	buf[12] = '\0';
	int num;
	guard = fscanf(file, " %12[^ \t\n]", buf);
	if (guard == EOF) {
		return guard;
	}
	guard = sscanf(buf, "%d", &num);
	if (guard != 1) {
		fscanf(file, "%*[^\n]%*c");
		printf("Введено не целое число! Введено: %s\n", buf);
		return 0;
	}
	if (is_int_overflow(buf)) {
	    fscanf(file, "%*[^\n]%*c");
	    printf("Слишком большое число! Введено: %s\n", buf);
	    return 0;
	}
	fscanf(file, "%*c");
	*target = num;
	return 1;
}


short scanfTxtFileUInt(unsigned int* target, FILE* file)
{
	short guard;
	char buf[12];
	// 12, т.к UINT_MAX содержит 10 цифр + '-' + один знак для оценки переполнения + '\0'
	buf[11] = '\0';
	unsigned int num;
	guard = fscanf(file, " %11[^ \t\n]", buf);
	if (guard == EOF) {
		return guard;
	}
	guard = sscanf(buf, "%u", &num);
	if (guard != 1) {
		fscanf(file, "%*[^\n]%*c");
		printf("Введено не целое число! Введено: %s\n", buf);
		return 0;
	}
	if (buf[0] == '-') {
		fscanf(file, "%*[^\n]%*c");
		printf("Введено отрицательное число! Введено: %s\n", buf);
		return 0;
	}
	if (is_uint_overflow(buf)) {
	    fscanf(file, "%*[^\n]%*c");
	    printf("Слишком большое число! Введено: %s\n", buf);
	    return 0;
	}
	fscanf(file, "%*c");
	*target = num;
	return 1;
}


short scanfBinFileInt(int* target, FILE* file)
{
	int num;
	fread(&num, sizeof(int), 1, file);
	if (ferror(file))
		return 0;
	if (feof(file))
		return EOF;

	*target = num;
	return 1;
}


short is_int_overflow(char s[13])
{
    char s2[13];
    s2[11] = '\0';
    if (s[0] == '-') {
		sprintf(s2, "%d", INT_MIN);
    }
    else {
		sprintf(s2, "%d", INT_MAX);
		s2[10] = '\0';
    }
    short diff = strlen(s) - strlen(s2);
    if (diff) {
    	return diff > 0;
    }
    if (strcmp(s, s2) > 0) {
		return 1;
    }
    return 0;
}


short is_uint_overflow(char s[12])
{
	char s2[11];
	sprintf(s2, "%u", UINT_MAX);
	s2[10] = '\0';
    int diff = strlen(s) - strlen(s2);
    if (diff) {
    	return diff > 0;
    }
    if (strcmp(s, s2) > 0) {
		return 1;
    }
    return 0;
}


short readline(char* output, char** dest, FILE* file, short mode)
{
	short guard;
	switch (mode) {
	case CONSOLE_MODE:
		if (output) {
			printf("%s\n", output);
		}
		guard = readConsoleLine(dest);
		break;
	case TXTFILE_MODE:
		guard = readTxtFileLine(dest, file);
		break;
	}
	return guard;
}


short readConsoleLine(char** dest)
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


short readTxtFileLine(char** dest, FILE* file)
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
    fscanf(file, "%*[^\n0-9a-zA-Z]");
    do {
        n = fscanf(file, "%80[^\n]", buf);
        if (n == EOF) {
        	free(ptr);
        	return n;
        }
        if (n == 0) {
            fscanf(file, "%*c");
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


short read_y_or_n(char* dest)
{
	char ch[2];
	ch[0] = '\0';
	ch[1] = '\0';
	short guard;
	while (ch[1] != '\0' || !(*ch == 'y' || *ch == 'n')) {
		printf(">>> ");
		guard = scanf(" %2[^\n\t ]%*c", ch);
		if (guard == EOF) {
			return guard;
		}
		if (ch[1] != '\0' || !(*ch == 'y' || *ch == 'n')) {
			scanf("%*[^\n]%*c");
			printf("Type \"y\" or \"n\"!\n");
		}
	}
	*dest = *ch;
	return 1;
}


short read_int_inrange(void* dest, short type, int min, int max)
{
	int num;
	short guard = scanfIntType(&num, NULL, 0);
	if (guard == EOF) {
		return EOF;
	}
	while (num < min || num > max) {
		printf("Type an integer from %d to %d !\n", min, max);
		guard = scanfIntType(&num, NULL, 0);
		if (guard == EOF) {
			return EOF;
		}
	}
	switch (type) {
	case SHORT_TYPE:
		*(short*)dest = num;
		break;
	case INT_TYPE:
		*(int*)dest = num;
		break;
	case UINT_TYPE:
		*(unsigned int*)dest = num;
		break;
	}
	return 1;
}

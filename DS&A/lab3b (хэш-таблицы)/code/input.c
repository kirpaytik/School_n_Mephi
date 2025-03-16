#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include "mylib.h"


int scanfInt(int* target, FILE* file, int mode)
{
	int guard;
	switch (mode) {
	case 0:
		guard = scanfConsoleInt(target);
		break;
	case 1:
		guard = scanfTxtFileInt(target, file);
		break;
	case 2:
		guard = scanfBinFileInt(target, file);
		break;
	}
	return guard;
}


int scanfUInt(unsigned int* target, FILE* file, int mode)
{
	int guard;
	switch (mode) {
	case 0:
		guard = scanfConsoleUInt(target);
		break;
	case 1:
		guard = scanfTxtFileUInt(target, file);
		break;
	case 2:
		// отдельная функция для UINT здесь даже не нужна
		int num;
		guard = scanfBinFileInt(&num, file);
		*target = num;
		break;
	}
	return guard;
}


int scanfConsoleInt(int* target)
{
	int guard, flag = 1;
	char buf[13];
	// 13, т.к INT_MAX содержит 10 цифр + '-' + один знак для оценки переполнения + '\0'
	buf[12] = '\0';
	int num;
	while (flag == 1)
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
		scanf("%*c");
		flag = 0;
	}
	*target = num;
	return 1;
}


int scanfConsoleUInt(unsigned int* target)
{
	int guard, flag = 1;
	char buf[12];
	// 12, т.к UINT_MAX содержит 10 цифр + '-' + один знак для оценки переполнения + '\0'
	buf[11] = '\0';
	unsigned int num;
	while (flag == 1)
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
		scanf("%*c");
		flag = 0;
	}
	*target = num;
	return 1;
}


int scanfTxtFileInt(int* target, FILE* file)
{
	int guard;
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


int scanfTxtFileUInt(unsigned int* target, FILE* file)
{
	int guard;
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


int scanfBinFileInt(int* target, FILE* file)
{
	int guard, num;
	guard = fread(&num, sizeof(int), 1, file);
	if (!guard) {
		return 0;
	}
	*target = num;
	return 1;
}


int is_int_overflow(char s[13])
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
    int diff = strlen(s) - strlen(s2);
    if (diff) {
    	return diff > 0;
    }
    if (strcmp(s, s2) > 0) {
		return 1;
    }
    return 0;
}


int is_uint_overflow(char s[12])
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


int readline(char* output, char** dest)
{
	printf("%s", output);

    char *ptr = (char*)malloc(1);
    if (ptr == NULL) {
        printf("Не найдено свободной памяти\n");
        return 0;
    }
    *ptr = '\0';
    char buf[81];
    int n=0, len=0;
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


int remove_end_spaces(char** dest)
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


int read_y_or_n(char* dest)
{
	char ch[2];
	ch[0] = '\0';
	ch[1] = '\0';
	int guard;
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


int read_int_inrange(int* dest, int min, int max)
{
	int num;
	int guard = scanfInt(&num, NULL, 0);
	if (guard == EOF) {
		return EOF;
	}
	while (num < min || num > max) {
		printf("Type an integer from %d to %d !\n", min, max);
		guard = scanfInt(&num, NULL, 0);
		if (guard == EOF) {
			return EOF;
		}
	}
	*dest = num;
	return 1;
}

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include "mylib.h"


int safeScanfInt(int* target)
{
	int guard, flag = 1;
	char buf[13];
	// 13, т.к INT_MAX содержит 10 цифр + '-' + один знак для оценки переполнения + '\0'
	buf[12] = '\0';
	int num;
	while (flag == 1)
	{
		printf(">>> ");
		guard = scanf(" %12[^ \t\n/]%*c", buf);
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
		flag = 0;
	}
	*target = num;
	return 1;
}


int safeScanfUInt(unsigned int* target)
{
	int guard, flag = 1;
	char buf[12];
	// 12, т.к UINT_MAX содержит 10 цифр + '-' + один знак для оценки переполнения + '\0'
	buf[11] = '\0';
	unsigned int num;
	while (flag == 1)
	{
		printf(">>> ");
		guard = scanf(" %11[^ \t\n/]%*c", buf);
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
		flag = 0;
	}
	*target = num;
	return 1;
}


int safeFileScanfInt(int* target, FILE* file)
{
	int guard;
	char buf[13];
	// 13, т.к INT_MAX содержит 10 цифр + '-' + один знак для оценки переполнения + '\0'
	buf[12] = '\0';
	int num;
	guard = fscanf(file, " %12[^ \t\n/]%*c", buf);
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
	*target = num;
	return 1;
}


int safeFileScanfUInt(unsigned int* target, FILE* file)
{
	int guard;
	char buf[12];
	// 12, т.к UINT_MAX содержит 10 цифр + '-' + один знак для оценки переполнения + '\0'
	buf[11] = '\0';
	unsigned int num;
	guard = fscanf(file, " %11[^ \t\n/]%*c", buf);
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


char* readline(char* output)
{
    printf("%s", output);

    char *ptr = (char*)malloc(1);
    if (ptr == NULL) {
        printf("Не найдено свободной памяти\n");
        return NULL;
    }
    *ptr = '\0';
    char buf[81];
    int n=0, len=0;
    char* temp = NULL;
    do {
        scanf("%*[^\n0-9a-zA-Z]");
        n = scanf("%80[^\n]", buf);
        if (n == EOF) {
        	free(ptr);
        	ptr = (char*)malloc(sizeof(char));
        	*ptr = '\0';
        	return ptr;
        }
        if (n < 0) {
            free(ptr);
            ptr = NULL;
            continue;
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
                return NULL;
            }
            ptr = temp;
            strcat(ptr, buf);
        }
    } while (n > 0);

    return ptr;
}


char* readFileLine(char* output, FILE* file)
{
    printf("%s", output);

    char *ptr = (char*)malloc(1);
    if (ptr == NULL) {
        printf("Не найдено свободной памяти\n");
        return NULL;
    }
    *ptr = '\0';
    char buf[81];
    int n=0, len=0;
    char* temp = NULL;
    do {
        fscanf(file, "%*[^\n0-9a-zA-Z]");
        n = fscanf(file, "%80[^\n]", buf);
        if (n == EOF) {
        	free(ptr);
        	return NULL;
        }
        if (n < 0) {
            free(ptr);
            ptr = NULL;
            continue;
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
                return NULL;
            }
            ptr = temp;
            strcat(ptr, buf);
        }
    } while (n > 0);

    return ptr;
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "fwrite.h"

int safeScanfInt(int *target)
{
	int guard, flag = 1;
	char buf[13];
	// 13, т.к INT_MIN содержит 10 цифр + '-' + один знак для оценки переполнения + '\0'
	buf[12] = '\0';
	int num;
	while (flag == 1)
	{
	    scanf("%*[\n]");
		guard = scanf("%12[^ \n]", buf);
		scanf("%*[^0-9-\n]");
		if (guard == EOF) {
			return 0;
		}
		guard = sscanf(buf, "%d", &num);
		if (guard != 1) {
			printf("Введите целое число!\n");
			scanf("%*[^\n]");
			continue;
		}
		if (check_for_overflow(buf)) {
		    printf("Слишком большое число!\n");
		    scanf("%*[^\n]");
		    continue;
		}
		flag = 0;
	}
	*target = num;
	return 1;
}

int check_for_overflow(char s[13])
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
    if (strlen(s) < strlen(s2)) {
		return 0;
    }
    if (strlen(s) > strlen(s2)) {
		return 1;
    }
    if (strcmp(s, s2) > 0) {
		return 1;
    }
    return 0;
}

int inputMatr(FILE *filePointer)
{
	printf("Введите количество строк матрицы\n");
	int returned;
	int len = 0;
	while (len < 1) {
		returned = safeScanfInt(&len);
		if (returned == 0) {
			return 0;
		}
		if (len < 1) {
			printf("Введите число большее нуля!\n");
		}
	}
	fwrite(&len, sizeof(int), 1, filePointer);
	int *n = (int*)malloc(len * sizeof(int));
	int i, j;
	for (i = 0; i < len; i++) {
		printf("Введите количество стлобцов %d-ой строки\n", i+1);
		n[i] = -1;
		while (n[i] < 1) {
			returned = safeScanfInt(&n[i]);
			if (returned == 0) {
				free(n);
				return 0;
			}
			if (n[i] < 1) {
				printf("Введите число большее нуля!\n");
			}
		}
	}
	int offset = 1 + 2*len;
	for (i = 0; i < len; i++) {
		fwrite(&n[i], sizeof(int), 1, filePointer);
		fwrite(&offset, sizeof(int), 1, filePointer);
		offset += n[i];
	}
	int elem;
	for (i = 0; i < len; i++) {
		printf("Введите %d элементов %d-ой строки\n", n[i], i+1);
		for (j = 0; j < n[i]; j++) {
			returned = safeScanfInt(&elem);
			if (returned == 0) {
				free(n);
				return 0;
			}
			fwrite(&elem, sizeof(int), 1, filePointer);
		}
	}
	free(n);
	return 1;
}

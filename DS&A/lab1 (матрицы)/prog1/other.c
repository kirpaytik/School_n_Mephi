#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "other.h"

void freeMatr(Matrix *matr)
{
	if (matr == NULL) {
		return;
	}
	Array *arr = NULL;
	int i;
	for (i = 0; i < matr->len; i++) {
		arr = matr->ptr + i;
		free(arr->ptr);
		// без free(arr), т.к не сущ указателя на каждый arr
	}
	free(matr->ptr);
	// без free(matr), т.к изначально (т.е в main) нет указателя
}

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

int inputMatr(Matrix *matr)
{
	printf("Введите количество строк матрицы\n");
	int returned;
	matr->len = 0;
	int length = 0;
	while (length < 1) {
		returned = safeScanfInt(&length);
		if (returned == 0) {
			return 0;
		}
		if (length < 1) {
			printf("Введите число большее нуля!\n");
		}
	}
	matr->ptr = (Array*)malloc(length * sizeof(Array));
	matr->ptr[0].ptr = NULL;
	if (matr->ptr == NULL) {
		return 0;
	}
	int i;
	for (i = 0; i < length; i++) {
		returned = inputArray(matr->ptr + i, i);
		matr->len++;
		if (returned == 0) {
			return 0;
		}
	}
	return 1;
}

int inputArray(Array *arr, int arrnum)
{
	printf("Введите количество стлобцов %d-ой строки\n", arrnum+1);
	int returned;
	arr->len = 0;
	arr->ptr = NULL;
	int length = 0;
	while (length < 1) {
		returned = safeScanfInt(&length);
		if (returned == 0) {
			return 0;
		}
		if (length < 1) {
			printf("Введите число большее нуля!\n");
		}
	}
	arr->ptr = (int*)malloc(length * sizeof(int));
	if (arr->ptr == NULL) {
		return 0;
	}
	printf("Введите %d элементов строки - целых чисел\n", length);
	int i;
	for (i = 0; i < length; i++) {
		returned = safeScanfInt(&(arr->ptr[i]));
		arr->len++;
		if (returned == 0) {
			return 0;
		}
	}
	return 1;
}

int getSumOfDigits(int number)
{
	number = abs(number);
	int sum = 0;
	while (number > 0)
	{
		sum += number % 10;
		number /= 10;
	}
	return sum;
}

void func(Matrix matr, Array arr)
{
	int first;
	int i,j;
	for (i = 0; i < matr.len; i++) {
		arr.ptr[i] = matr.ptr[i].ptr[0];
		first = getSumOfDigits(matr.ptr[i].ptr[0]);

		for (j = 1; j < matr.ptr[i].len; j++) {
			if (getSumOfDigits(matr.ptr[i].ptr[j]) == first) {
				arr.ptr[i] += matr.ptr[i].ptr[j];
			}
		}
	}
}
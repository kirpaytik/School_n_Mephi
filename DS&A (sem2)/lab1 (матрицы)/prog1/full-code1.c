#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Array {
	int *ptr;
	int len;
} Array;

typedef struct Matrix {
	Array *ptr;
	int len;
} Matrix;

int safeScanfInt(int *target);
int check_for_overflow(char s[13]);
int inputMatr(Matrix *matr);
int inputArray(Array *arr, int arrnum);

int getSumOfDigits(int number);
void func(Matrix matr, Array arr);

void freeMatr(Matrix *matr);

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
	while (matr->len < 1) {
		returned = safeScanfInt(&(matr->len));
		if (returned == 0) {
			return 0;
		}
		if (matr->len < 1) {
			printf("Введите число большее нуля!\n");
		}
	}
	matr->ptr = (Array*)malloc(matr->len * sizeof(Array));
	matr->ptr[0].ptr = NULL;
	if (matr->ptr == NULL) {
		return 0;
	}
	int i;
	for (i = 0; i < matr->len; i++) {
		returned = inputArray(matr->ptr + i, i);
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
	while (arr->len < 1) {
		returned = safeScanfInt(&(arr->len));
		if (returned == 0) {
			return 0;
		}
		if (arr->len < 1) {
			printf("Введите число большее нуля!\n");
		}
	}
	arr->ptr = (int*)malloc(arr->len * sizeof(int));
	if (arr->ptr == NULL) {
		return 0;
	}
	printf("Введите %d элементов строки - целых чисел\n", arr->len);
	int i;
	for (i = 0; i < arr->len; i++) {
		returned = safeScanfInt(&(arr->ptr[i]));
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

int main()
{
	Matrix matr = {NULL, 0};
	int returned;
	returned = inputMatr(&matr);
	if (returned == 0) {
		freeMatr(&matr);
		printf("Завершение программы\n");
		return 0;
	}
	int i,j;
	printf("Вывод исходной матрицы:\n");
	for (i = 0; i < matr.len; i++) {
		for (j = 0; j < matr.ptr[i].len - 1; j++) {
			printf("%d ", matr.ptr[i].ptr[j]);
		}
		printf("%d\n", matr.ptr[i].ptr[j]);
	}

	Array res = {NULL, matr.len};
	res.ptr = (int*)malloc(matr.len * sizeof(int));
	if (res.ptr == NULL) {
		freeMatr(&matr);
		printf("Завершение программы\n");
		return 0;
	}
	func(matr, res);
	printf("Вывод результирующего вектора:\n");
	for (i = 0; i < res.len-1; i++) {
		printf("%d ", res.ptr[i]);
	}
		printf("%d\n", res.ptr[i]);

	freeMatr(&matr);
	printf("Конец программы\n");
	return 0;
}

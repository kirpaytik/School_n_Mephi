#include <stdio.h>
#include <stdlib.h>
#include "other.h"

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
	free(res.ptr);
	printf("Конец программы\n");
	return 0;
}
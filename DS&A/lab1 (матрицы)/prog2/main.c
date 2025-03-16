#include <stdio.h>
#include "other.h"

int main()
{
	Matrix matr;
	int returned = inputMatr(&matr);
	if (returned == 0) {
		printf("Заврешние программы\n");
		return 0;
	}
	Matrix res;
	func(matr, &res);
	printf("Вывод исходной матрицы:\n");
	outputMatr(matr);
	printf("Вывод результирующей матрицы:\n");
	outputMatr(res);

	printf("Конец программы\n");
	fclose(matr.fptr);
	fclose(res.fptr);
	return 0;
}

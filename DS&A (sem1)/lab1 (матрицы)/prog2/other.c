#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "other.h"

// typedef struct Matrix {
// 	FILE *fptr;
// 	int offset;
// } Matrix;

int inputMatr(Matrix *matr)
{
	char *fileName = readline("Введите название файла для считывания матрицы\n");
	matr->fptr = fopen(fileName, "r");
	if (matr->fptr == NULL) {
		printf("Ошибка при открытии файла!\n");
		return 0;
	}
	matr->offset = 0;
}

void outputMatr(Matrix matr)
{
	fseek(matr.fptr, matr.offset * sizeof(int), SEEK_SET);
	int i, j, ilen, jlen, offset, value;
	fread(&ilen, sizeof(int), 1, matr.fptr);
	for (i = 0; i < ilen; i++) {
		fseek(matr.fptr, (2*i + 1) * sizeof(int), SEEK_SET);
		fread(&jlen, sizeof(int), 1, matr.fptr);
		fread(&offset, sizeof(int), 1, matr.fptr);
		fseek(matr.fptr, offset*sizeof(int), SEEK_SET);
		for (j = 0; j < jlen; j++) {
			fread(&value, sizeof(int), 1, matr.fptr);
			printf("%d ", value);
		}
		printf("\n");
	}
}

int getMatrElem(Matrix matr, int index1, int index2)
{
	fseek(matr.fptr, matr.offset * sizeof(int), SEEK_SET);
	int ilen, jlen, offset, elem;
	fread(&ilen, sizeof(int), 1, matr.fptr);
	if (index1 == -1) {
		return ilen;
	}
	fseek(matr.fptr, index1 * 2 * sizeof(int), SEEK_CUR);
	fread(&jlen, sizeof(int), 1, matr.fptr);
	if (index2 == -1) {
		return jlen;
	}
	fread(&offset, sizeof(int), 1, matr.fptr);
	fseek(matr.fptr, offset * sizeof(int), SEEK_SET);
	fseek(matr.fptr, index2 * sizeof(int), SEEK_CUR);
	fread(&elem, sizeof(int), 1, matr.fptr);
	return elem;
}

int getSumOfDigits(int number)
{
	number = abs(number);
	int sum = 0;
	while (number > 0) {
		sum += number % 10;
		number /= 10;
	}
	return sum;
}

int func(Matrix matr, Matrix *res)
{
	char *fileName = "res-matr_temp.txt";
	res->fptr = fopen(fileName, "w");
	res->offset = 0;
	int first, resElem, elem;
	resElem = 1;
	fwrite(&resElem, sizeof(int), 1, res->fptr);
	resElem = getMatrElem(matr, -1, -1);
	fwrite(&resElem, sizeof(int), 1, res->fptr);
	resElem = 3;
	fwrite(&resElem, sizeof(int), 1, res->fptr);
	int i,j;
	for (i = 0; i < getMatrElem(matr, -1, -1); i++) {
		resElem = getMatrElem(matr, i, 0);
		first = getSumOfDigits(resElem);
		for (j = 1; j < getMatrElem(matr, i, -1); j++) {
			elem = getMatrElem(matr, i, j);
			if (getSumOfDigits(elem) == first) {
				resElem += elem;
			}
		}
		fwrite(&resElem, sizeof(int), 1, res->fptr);
	}
	fclose(res->fptr);
	res->fptr = fopen(fileName, "r");
	return 1;
}

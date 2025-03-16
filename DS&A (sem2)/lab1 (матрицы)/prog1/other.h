#ifndef OTHER_H
#define OTHER_H

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

#endif
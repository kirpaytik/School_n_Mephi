#ifndef OTHER_H
#define OTHER_H

#include <stdio.h>

typedef struct Matrix {
    FILE *fptr;
    int offset;
} Matrix;

int inputMatr(Matrix *matr);
int getMatrElem(Matrix matr, int index1, int index2);
void outputMatr(Matrix matr);

int getSumOfDigits(int number);
int func(Matrix matr, Matrix *res);

#endif

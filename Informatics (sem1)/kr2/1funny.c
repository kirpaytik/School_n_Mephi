#include "funny.h"
#include <stdlib.h>
#include <string.h>

void process1 (int** array, int* size)
{
	int i,j;
	for (i = 0; i < *size; i++) {
		if ((*array)[i] > 9) {
			*array = realloc(*array, ((*size)+1)*sizeof(int));
			(*size)++;
			for (j = (*size)-1; j > i+1; j--) {
				(*array)[j] = (*array)[j-1];
			}
			
			(*array)[i+1] = (*array)[i] % 10;
			(*array)[i] /= 10;
			i--;
		}
	}
}
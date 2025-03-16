#include "funny.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int* massive = calloc(3, sizeof(int));
	int size = 3;
	for (int i = 0; i < size; i++) {
		scanf("%d", &massive[i]);
	}
	for (int i = 0; i < size; i++) {
		printf("%d ", massive[i]);
	}
	printf("\n");
	process1(&massive, &size);
	for (int i = 0; i < size; i++) {
		printf("%d ", massive[i]);
	}
	
	return 0;
}
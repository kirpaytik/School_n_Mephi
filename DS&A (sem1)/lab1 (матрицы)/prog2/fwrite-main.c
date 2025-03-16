#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "fwrite.h"

int main()
{
	char *fileName = readline("Задайте имя файла для записи данных\n");
	FILE *filePointer = fopen(fileName, "w");
	free(fileName);
	if (filePointer == NULL) {
		printf("Ошибка при открытии файла!\n");
		return 0;
	}
	int returned = inputMatr(filePointer);
	if (returned == 0) {
		printf("Заврешение программы\n");
		fclose(filePointer);
		return 0;
	}

	printf("Конец программы\n");
	fclose(filePointer);
	return 0;
}

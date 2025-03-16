// Это говно, а не генератор, к слову. Но пусть будет))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <limits.h>
#include <time.h>

int safeScanfInt(int *target);
int check_fow_overflow(char s[13]);

int genMatr(int ilen, int jlen);
int randIntWithSumOfDigits(int number);
int getSumOfDigits(int number);

int safeScanfInt(int *target)
{
	int guard, flag = 1;
	char buf[13];
	buf[12] = '\0';int num;
	while (flag == 1) {
		scanf("%*[\n]");
		guard = scanf("%12[^ \n]", buf);
		if (guard == EOF) {
			return 0;
		}
		guard = sscanf(buf, "%d", &num);
		if (guard != 1) {
			printf("Введите целое число!\n");
			scanf("%*[^\n]");
			continue;
		}
		if (check_fow_overflow(buf)) {
			printf("Слишком большое число!\n");
			scanf("%*[^\n]");
			continue;
		}
		flag = 0;
	}
	*target = num;
	return 1;
}

int check_fow_overflow(char s[13])
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
	if (strcmp(s, s2)  > 0) {
		return 1;
	}
	return 0;
}

int genMatr(int ilen, int jlen)
{
	char *fileName = readline("Введите имя файла для записи матрицы\n");
	FILE *filePointer = fopen(fileName, "w");
	free(fileName);
	if (filePointer == NULL) {
		printf("Ошибка открытия файла!\n");
		return 0;
	}
	srand(clock());
	fwrite(&ilen, sizeof(int), 1, filePointer);
	int *n = (int*)malloc(ilen * sizeof(int));
	int i, j, jjlen;
	for (i = 0; i < ilen; i++) {
		jjlen = rand() % jlen;
		if (jjlen == 0) {
			jjlen++;
		}
		n[i] = jjlen;
	}
	int offset = 1 + 2*ilen;
	for (i = 0; i < ilen; i++) {
		fwrite(&(n[i]), sizeof(int), 1, filePointer);
		fwrite(&offset, sizeof(int), 1, filePointer);
		offset += n[i];
	}
	int elem, first, probability;
	for (i = 0; i < ilen; i++) {
		first = rand() % 1000;
		fwrite(&first, sizeof(int), 1, filePointer);
		for (j = 1; j < n[i]; j++) {
			probability = rand() % 100;
			if (probability < 33) {
				elem = randIntWithSumOfDigits(first);
			}
			else {
				elem = rand() % 1000;
			}
			probability = rand() % 100;
			if (probability < 50) {
				elem = -elem;
			}
			fwrite(&elem, sizeof(int), 1, filePointer);
		}
	}
	free(n);
}

int randIntWithSumOfDigits(int number)
{
	int sumOfDigits = getSumOfDigits(number);
	int i;
	srand(clock());
	int probability = rand() % 100;
	if (probability < 50) {
		for (i = 0; i < 1000; i++) {
			if (getSumOfDigits(i) == sumOfDigits) {
				return i;
			}
		}
	}
	for (i = 999; i > -1; i--) {
		if (getSumOfDigits(i) == sumOfDigits) {
			return i;
		}
	}
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

int main()
{
	int ilen = -1, jlen = -1;
	int returned;
	printf("Введите количество строк матрицы\n");
	while (ilen < 1) {
		returned = safeScanfInt(&ilen);
		if (returned == 0) {
			printf("Завершение программы\n");
			return 0;
		}
		if (ilen < 1) {
			printf("Введите число большее нуля!\n");
			continue;
		}
	}
	printf("Введите максимальное количество столбцов строки\n");
	while (jlen < 1) {
		returned = safeScanfInt(&jlen);
		if (returned == 0) {
			printf("Завершение программы\n");
			return 0;
		}
		if (jlen < 1) {
			printf("Введите число большее нуля!\n");
			continue;
		}
	}
	printf("Генерация матрицы\n");
	returned = genMatr(ilen, jlen);
	if (returned == 0) {
		printf("Завершение программы\n");
		return 0;
	}

	printf("Конец программы\n");
	return 0;
}

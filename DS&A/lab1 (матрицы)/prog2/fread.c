#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

int main()
{
    char *fileName = readline("Введите имя файла для чтения матрицы\n");
    FILE *fptr = fopen(fileName, "r");
    free(fileName);
    if (fptr == NULL) {
        printf("Ошибка при открытии файла!\n");
        return 0;
    }
    int len, c;
    fread(&len, sizeof(int), 1, fptr);
    printf("Количество строк матрицы: %d\n", len);
    int *n = (int*)malloc(len * sizeof(int));
    int i,j;
    printf("Колчиство столбцов строки - смещение в файле\n");
    for (i = 0; i < len; i++) {
        fread(&c, sizeof(int), 1, fptr);
        n[i] = c;
        printf("%d-", c);
        fread(&c, sizeof(int), 1, fptr);
        printf("%d ", c);
    }
    printf("Вывод всех элементов матрицы\n");
    for (i = 0; i < len; i++) {
        printf("%d-я строка:\n", i+1);
        for (j = 0; j < n[i]; j++) {
            fread(&c, sizeof(int), 1, fptr);
            printf("%d ", c);
        }
        printf("\n");
    }

    printf("Конец программы\n");
    free(n);
    return 0;
}

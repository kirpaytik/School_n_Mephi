// тест, что если реаалокнуть на столько же места, сколько и было - всё ок
// а затем на меньше, чем было - всё плохо

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *a = (int*)malloc(5 * sizeof(int));
	int i;
	for (i = 0; i < 5; i++) {
		a[i] = i % 3;
	}
	a = (int*)realloc(a, 5 * sizeof(int));
	printf("Вывод массива после реаллока на то же число байт, что и было:\n");
	for (i = 0; i < 5; i++) {
		printf("%d ", a[i]);
	}
	printf("\nВсё ок\n");

	// a[4] = 0;
	// a = (int*)realloc(a, 4 * sizeof(int));
	// printf("Вывод массива после реаллока на объём памяти на 1 элемент меньше, чем было\n");
	// for (i = 0; i < 5; i++) {
	//      printf("%d ", a[i]);
	// }
	// printf("\nВсё плохо\n");

	free(a);
	return 0;
}

// тест, можно ли реаллокать указатель, если ещё не инициализировал значения
// ответ - можно
// зачем это делать - чтобы не разбивать на два случая:
// первый, когда нужен malloc(), и последующие, когда уже нужен realloc()

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *a = (int*)malloc(sizeof(int));
	a = (int*)realloc(a, 2 * sizeof(int));
	a[0] = 1;
	a[1] = 2;
	printf("%d %d\n", a[0], a[1]);

	free(a);
	return 0;
}

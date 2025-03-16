#include <stdio.h>
#include <stdlib.h>
#include "tablelib.h"


int dialog_put(Table *table)
{
	printf("Введите ключ для вставки\n>>> ");
	int key;
	scanf("%d%*c", &key);
	printf("Введите значение для вставки: 1 символ\n>>> ");
	char *info = (char*)malloc(2 * sizeof(char));
	scanf("%c", info);
	info[1] = '\0';

	return put_key(table, key, info);
}


int dialog_find(Table table)
{
	printf("Введите ключ для поиска\n>>> ");
	int key;
	scanf("%d%*c", &key);

	KeySpace ks = get_key(table, key);
	if (ks.info == NULL) {
		printf("Нет элемента с таким ключом!\n");
		return ERR;
	}
	printf("%d: %s\n", key, ks.info);
	return OK;
}


int dialog_del(Table *table)
{
	printf("Введите ключ для удаления\n>>> ");
	int key;
	scanf("%d%*c", &key);

	return del_key(table, key);
}


int dialogue(Table *table)
{
	printf("Введите размер таблицы\n>>> ");
	int size;
	scanf("%d%*c", &size);
	*table = create_table(size);

	int option = 100;
	while (option > 0) {
		printf("Выберите пункт меню:\n\
				1) Добавить элемент\n\
				2) Найти элемент\n\
				3) Удалить элемент\n\
				4) Вывести таблицу\n\
				5) Завершить программу\n>>> ");
		scanf("%d%*c", &option);
		switch (option) {
		case 1:
			dialog_put(table);
			print_table(*table);
			break;
		case 2:
			dialog_find(*table);
			break;
		case 3:
			dialog_del(table);
			print_table(*table);
			break;
		case 4:
			print_table(*table);
			break;
		case 5:
			return OK;
		}
	}
	return OK;
}


int main()
{
	printf("Если всё вводить правильно, то никаких ошибок или утечек\n");
	printf("Так как это тренировка, то на защиту от дурака я время не тратил\n");

	Table table;
	dialogue(&table);

	free_table(&table);
	return 0;
}

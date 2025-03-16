#include <stdio.h>
#include "mylib.h"

int main()
{
	// table - основная таблица
	// table2 - сюда будет производиться запись при команде find
	Table *table, *table2;
	int checker = create_table(&table);
	if (checker) {
		printf("Table creating error\n");
		endofprog(NULL, NULL);
		return 1;
	}
	checker = create_table(&table2);
	if (checker) {
		printf("Table creating error\n");
		endofprog(table, NULL);
		return 1;
	}

	checker = dialogue(table, table2);
	if (checker) {
		endofprog(table, table2);
		return 1;
	}

	printf("Successfully reached the end of program\n");
	endofprog(table, table2);
	return 0;
}
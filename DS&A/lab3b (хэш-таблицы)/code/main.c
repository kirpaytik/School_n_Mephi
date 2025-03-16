#include <stdio.h>
#include "mylib.h"

int main()
{
	Table* table;
	int checker = create_table(&table);
	if (checker) {
		printf("Table creating error\n");
		endofprog(NULL);
		return 1;
	}

	checker = dialogue_start(table);
	if (checker) {
		endofprog(table);
		return 1;
	}

	printf("Successfully reached the end of program\n");
	endofprog(table);
	return 0;
}
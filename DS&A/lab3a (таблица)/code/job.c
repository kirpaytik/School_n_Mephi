#include <stdlib.h>
#include "mylib.h"
#include "table.h"

#define OK 0
#define BAD 1


int create_table(Table** dest)
{
	return t_create(dest);
}


void endofprog(Table* table1, Table* table2)
{
	t_free(table1);
	free(table1);
	t_free(table2);
	free(table2);
}

// Принимает указатель, потому что в dialog.c нет инклюда table.h,
// и там он ещё не знает о внутренностях
void job_print_console(Table* table)
{
	t_print_console(table);
}


void job_print_file(Table* table, FILE* file)
{
	t_print_file(table, file);
}


int job_insert(Table* table, unsigned int key, char* info)
{
	KeySpace ks = (KeySpace){key, -1, info};
	int checker = t_insert(table, ks);
	if (checker) {
		return BAD;
	}
	return OK;
}


int job_delete(Table* table, unsigned int key, int rel)
{
	int checker = t_delete(table, key, rel);
	if (checker) {
		return BAD;
	}
	return OK;
}


int job_clear(Table* table)
{
	t_free(table);
	return OK;
}


int job_find(Table* table, unsigned int key, int rel, Table* table2)
{
	int checker = t_find(table, key, rel, table2);
	if (checker) {
		return BAD;
	}
	if (t_is_empty(table2)) {
		return 2;
	}
	t_print_console(table2);
	return OK;
}

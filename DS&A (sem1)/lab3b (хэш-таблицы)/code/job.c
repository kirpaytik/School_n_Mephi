#include <stdlib.h>
#include "mylib.h"
#include "table.h"

#define OK 0
#define BAD 1
#define PASS 3


int create_table(Table** dest)
{
	return t_create(dest);
}


void endofprog(Table* table)
{
	t_free(table);
	free(table);
}

// force отвечает за принудительную смену размера
// если 0, то размер сменится лишь при необходимости
int job_set_size(Table* table, int msize, int force)
{
	if (force == 0 && t_get_msize(table) >= t_get_csize(table) + msize) {
		return OK;
	}
	return t_set_size(table, t_get_newsize(msize));
}


void job_print(Table* table, FILE* file, int mode)
{
	switch (mode) {
	case 0:
		t_print_console(table);
		break;
	case 1:
		t_print_txtfile(table, file);
		break;
	case 2:
		t_print_binfile(table, file);
		break;
	}
}


int job_insert(Table* table, unsigned int key, int info)
{
	KeySpace ks = (KeySpace){1, key, info};
	int checker = t_insert(table, ks);
	return checker;
}


int job_delete(Table* table, unsigned int key)
{
	if (t_is_empty(table)) {
		return PASS;
	}
	int checker = t_delete(table, key);
	return checker;
}


int job_clear(Table* table)
{
	if (t_is_empty(table)) {
		return PASS;
	}
	int checker = t_clear(table);
	return checker;
}


int job_find(Table* table, unsigned int key, KeySpace* dest)
{
	int checker = t_find(table, key, dest);
	return checker;
}

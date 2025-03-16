#include <stdio.h>
#include <stdlib.h>
#include "tablelib.h"


Table create_table(int size)
{
	Table table = (Table){NULL, 0, 0};
	table.ks = (KeySpace*)malloc(size * sizeof(KeySpace));
	table.msize = size;
	table.csize = 0;
	return table;
}


void print_table(Table table)
{
	printf("Вывод таблицы\n");
	int i;
	for (i = 0; i < table.csize; i++) {
		printf("%d: %s\n", table.ks[i].key, table.ks[i].info);
	}
}


void free_table(Table *table)
{
	int i;
	for (i = 0; i < table->csize; i++) {
		free(table->ks[i].info);
	}
	free(table->ks);
	table->csize = 0;
	table->msize = 0;
}


int find_key(Table table, int key)
{
	int i;
	for (i = 0; i < table.csize; i++) {
		if (table.ks[i].key == key) {
			return i;
		}
	}
	return NDef;
}


KeySpace get_key(Table table, int key)
{
	int indx = find_key(table, key);
	if (indx < 0) {
		return (KeySpace){0, NULL};
	}
	return table.ks[indx];
}


int put_key(Table *table, int key, char *info)
{
	if (table->csize >= table->msize) {
		free(info);
		return ERR;
	}
	if (find_key(*table, key) > -1) {
		free(info);
		return ERR;
	}
	table->ks[table->csize] = (KeySpace){key, info};
	(table->csize)++;
	return OK;
}


int del_key(Table *table, int key)
{
	int i = find_key(*table, key);
	if (i < 0) {
		return ERR;
	}
	free(table->ks[i].info);
	table->ks[i] = table->ks[table->csize - 1];
	table->ks[table->csize - 1] = (KeySpace){0, NULL};
	(table->csize)--;
	return OK;
}

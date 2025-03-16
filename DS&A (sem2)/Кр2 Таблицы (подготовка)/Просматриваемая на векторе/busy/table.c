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
		if (table.ks[i].busy == 0) {
			continue;
		}
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
		if (table.ks[i].busy == 1 && table.ks[i].key == key) {
			return i;
		}
	}
	return NDef;
}


KeySpace get_key(Table table, int key)
{
	int indx = find_key(table, key);
	if (indx < 0) {
		return (KeySpace){0, 0, NULL};
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
	table->ks[table->csize] = (KeySpace){1, key, info};
	(table->csize)++;
	return OK;
}


void garbage(Table *table)
{
	int i, j = 0;
	for (i = 0; i < table->csize; i++) {
		if (table->ks[i].busy == 1) {
			table->ks[j] = table->ks[i];
			j++;
		}
	}
	table->csize = j;
}


int del_key(Table *table, int key)
{
	int i = find_key(*table, key);
	if (i < 0) {
		return ERR;
	}
	table->ks[i].busy = 0;
	return OK;
}

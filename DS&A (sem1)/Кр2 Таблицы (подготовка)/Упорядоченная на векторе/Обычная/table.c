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
	if (table.csize == 0) {
		return NDef;
	}
	int l = 0, r = table.csize - 1;
	int mid;
	while (r - l > 1) {
		mid = (l + r) / 2;
		if (key < table.ks[mid].key) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	if (table.ks[l].key == key) {
		return l;
	}
	if (table.ks[r].key == key) {
		return r;
	}
	return Ndef;
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
	int indx = put_where(*table, key);
	int i;
	for (i = table->csize; i > indx; i--) {
		table->ks[i] = table->ks[i - 1];
	}
	table->ks[indx] = (KeySpace){key, info};
	(table->csize)++;
	return OK;
}


int put_where(Table table, int key)
{
	if (table.csize == 0) {
		return 0;
	}
	if (key > table.ks[table.csize - 1].key) {
		return table.csize;
	}
	int l = 0, r = table.csize - 1;
	int mid;
	while (r - l > 1) {
		mid = (l + r) / 2;
		if (key < table.ks[mid].key) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	if (table.ks[l].key < key) {
		return r;
	}
	return l;
}


int del_key(Table *table, int key)
{
	int indx = find_key(*table, key);
	if (indx < 0) {
		return ERR;
	}
	// Если добавить (11,"a"), удалить 11, добавить (11,"b") и попробовать удалить 11,
	// то почему-то он ругается на эту фришку,
	// хотя даже написав char *c = table->ks[indx].info; дебаг показывает всё нормально, что c = "b"
	free(table->ks[indx].info);
	int i;
	for (i = indx; i < table->csize - 1; i++) {
		table->ks[i] = table->ks[i + 1];
	}
	table->ks[table->csize] = (KeySpace){0, NULL};
	(table->csize)--;
	return OK;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "table.h"

#define OK 0
#define BAD 1

struct Table {
	KeySpace *ks;
	int msize;
	int csize;
};


int t_create(Table** dest)
{
	Table* table = (Table*)malloc(sizeof(Table));
	if (table == NULL) {
		printf("Memory allocation error\n");
		return BAD;
	}
	table->ks = NULL;
	table->msize = 0;
	table->csize = 0;
	*dest = table;
	return OK;
}


int t_set_size(Table* table, int msize)
{
	// calloc, т.к. busy надо везде 0
	KeySpace* ks = (KeySpace*)calloc(msize, sizeof(KeySpace));
	if (ks == NULL) {
		printf("Memory allocation error\n");
		return BAD;
	}
	if (table->ks == NULL) {
		table->ks = ks;
		table->msize = msize;
		return OK;
	}
	Table table2 = (Table){ks, msize, 0};
	int i;
	for (i = 0; i < table->msize; i++) {
		if (table->ks[i].busy == 1) {
			// не может что-либо пойти не так, поэтому без checker
			t_insert(&table2, table->ks[i]);
		}
	}
	t_free(table);
	*table = table2;
	return OK;
}


void t_free(Table* table)
{
	if (!table) {
		return;
	}
	free(table->ks);
	table->ks = NULL;
	table->msize = 0;
	table->csize = 0;
}


void t_print_console(Table* table)
{
	printf("Table's size is: %d\n", table->msize);
	if (t_is_empty(table)) {
		printf("The table is empty\n");
		return;
	}
	int i;
	KeySpace ks;
	for (i = 0; i < table->msize; i++) {
		ks = table->ks[i];
		if (ks.busy == 1) {
			printf("%u %u\n", ks.key, ks.info);
		}
	}
}


void t_print_txtfile(Table* table, FILE* file)
{
	fprintf(file, "%d\n", table->csize);
	int i;
	KeySpace ks;
	for (i = 0; i < table->msize; i++) {
		ks = table->ks[i];
		if (ks.busy == 1) {
			fprintf(file, "%u %u\n", ks.key, ks.info);
		}
	}
}


void t_print_binfile(Table* table, FILE* file)
{
	fwrite(&table->csize, sizeof(int), 1, file);
	int i;
	KeySpace ks;
	for (i = 0; i < table->msize; i++) {
		ks = table->ks[i];
		if (ks.busy == 1) {
			fwrite(&ks.key, sizeof(int), 1, file);
			fwrite(&ks.info, sizeof(int), 1, file);
		}
	}
}


int t_insert(Table* table, KeySpace ks)
{
	if (table->csize == table->msize) {
		if (table->msize > INT_MAX / 5 * 4) {
			return -2;
		}
		int newsize = t_get_newsize(table->msize * 1.25);
		if (newsize == -1) {
			return -2;
		}
		int checker = t_set_size(table, newsize);
		if (checker == BAD) {
			return -2;
		}
	}
	unsigned int pos, step;
	pos = hash1(ks.key, table->msize);
	step = hash2(ks.key, table->msize);
	// получить h1 и h2 - доделать!
	int i;
	for (i = 0; i < table->msize; i++, pos += step) {
		pos %= table->msize;
		if (table->ks[pos].busy < 1) {
			break;
		}
		if (table->ks[pos].key == ks.key) {
			return -1;
		}
	}
	table->ks[pos] = ks;
	table->csize++;
	return OK;
}


int t_get_newsize(int newsize)
{
	while (!isPrime(newsize)) {
		if (newsize == INT_MAX) {
			return -1;
		}
		newsize++;
	}
	return newsize;
}


int isPrime(int num) {
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}


int t_delete(Table* table, unsigned int key)
{
	unsigned int pos, step;
	pos = hash1(key, table->msize);
	step = hash2(key, table->msize);
	// получить h1 и h2 - доделать!
	int i;
	for (i = 0; i < table->msize; i++, pos += step) {
		pos %= table->msize;
		if (table->ks[pos].busy == -1) {
			continue;
		}
		if (table->ks[pos].busy == 0) {
			return -1;
		}
		if (table->ks[pos].key == key) {
			table->ks[pos].busy = -1;
			table->csize--;
			return 0;
		}
	}
	return -1;
}


int t_find(Table* table, unsigned int key, KeySpace* dest)
{
	unsigned int pos, step;
	pos = hash1(key, table->msize);
	step = hash2(key, table->msize);
	// получить h1 и h2 - доделать!
	int i;
	for (i = 0; i < table->msize; i++, pos += step) {
		pos %= table->msize;
		if (table->ks[pos].busy == -1) {
			continue;
		}
		if (table->ks[pos].busy == 0) {
			return -1;
		}
		if (table->ks[pos].key == key) {
			dest->info = table->ks[pos].info;
			dest->key = key;
			dest->busy = 1;
			return 0;
		}
	}
	return -1;
}


int t_clear(Table* table)
{
	int i;
	for (i = 0; i < table->msize; i++) {
		table->ks[i] = (KeySpace){0, 0, 0};
	}
	table->csize = 0;
	return OK;
}


int t_is_empty(Table* table)
{
	return table->csize == 0;
}


int t_get_msize(Table* table)
{
	return table->msize;
}


int t_get_csize(Table* table)
{
	return table->csize;
}

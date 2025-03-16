#include <stdio.h>
#include <stdlib.h>
#define USE_ITER
#include "table.h"

#define OK 0
#define BAD 1

struct Table {
	Node* head;
	Node* last;
};

struct Iter {

};


int t_create(Table** dest)
{
	Table* table = (Table*)malloc(sizeof(Table));
	if (table == NULL) {
		printf("Memory allocation error\n");
		return BAD;
	}
	table->head = NULL;
	table->last = NULL;
	*dest = table;
	return OK;
}

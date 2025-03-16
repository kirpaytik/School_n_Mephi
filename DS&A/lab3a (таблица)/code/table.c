#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

#define OK 0
#define BAD 1

struct Table {
	Node* head;
	Node *last;
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


void t_free(Table* table)
{
	if (!table) {
		return;
	}
	Node* node = table->head;
	Node* next;
	while (node) {
		next = node->next;
		free(node->data.info);
		free(node);
		node = next;
	}
	table->head = NULL;
	table->last = NULL;
}


void t_print_console(Table* table)
{
	if (t_is_empty(table)) {
		printf("The table is empty\n");
		return;
	}
	Node* node = table->head;
	KeySpace ks;
	while (node) {
		ks = node->data;
		printf("%d %d %s\n", ks.key, ks.rel, ks.info);
		node = node->next;
	}
}


void t_print_file(Table* table, FILE* file)
{
	Node* node = table->head;
	KeySpace ks;
	while (node) {
		ks = node->data;
		fprintf(file, "%d %d %s\n", ks.key, ks.rel, ks.info);
		node = node->next;
	}
}


int t_insert(Table* table, KeySpace ks)
{
	Node* new = (Node*)malloc(sizeof(Node));
	if (new == NULL) {
		printf("Memory allocation error\n");
		return BAD;
	}
	if (ks.rel == -1) {
		ks.rel = t_find_lastrel(*table, ks.key);
	}
	new->data = ks;
	new->next = NULL;
	if (t_is_empty(table)) {
		new->prev = NULL;
		table->head = new;
		table->last = new;
		return OK;
	}
	new->prev = table->last;
	table->last->next = new;
	table->last = new;
	return OK;
}


int t_find_lastrel(Table table, unsigned int key)
{
	int rel = 0;
	Node* node = table.head;
	while (node) {
		if (node->data.key == key && node->data.rel > rel) {
			rel = node->data.rel;
		}
		node = node->next;
	}
	return rel + 1;
}


int t_delete(Table* table, unsigned int key, int rel)
{
	int checker;
	int flag = 0;
	Node* node = table->head;
	Node* next;
	while (node) {
		next = node->next;
		if (node->data.key == key && (node->data.rel == rel || rel == 0)) {
			checker = t_remove(table, node);
			flag = 1;
			if (checker) {
				return BAD;
			}
			if (rel) {
				return OK;
			}
		}
		node = next;
	}
	if (!flag) {
		printf("No such keys were found!\n");
	}
	return OK;
}


int t_remove(Table* table, Node* node)
{
	if (node->next) {
		node->next->prev = node->prev;
	}
	if (node->prev) {
		node->prev->next = node->next;
	}
	else {
		table->head = node->next;
	}
	if (!node->next) {
		table->last = node->prev;
	}
	free(node->data.info);
	free(node);
	return OK;
}


int t_find(Table* table, unsigned int key, int rel, Table* dest)
{
	int checker;
	Node* node = table->head;
	KeySpace ks;
	while (node) {
		if (node->data.key == key && (node->data.rel == rel || rel == 0)) {
			ks = (KeySpace){node->data.key, node->data.rel, NULL};
			ks.info = (char*)malloc((strlen(node->data.info) + 1) * sizeof(char));
			if (!ks.info) {
				printf("Memory allocation error\n");
				return BAD;
			}
			strcpy(ks.info, node->data.info);
			checker = t_insert(dest, ks);
			if (checker) {
				return BAD;
			}
			if (rel) {
				return OK;
			}
		}
		node = node->next;
	}
	return OK;
}


int t_is_empty(Table* table)
{
	return table->head == NULL;
}

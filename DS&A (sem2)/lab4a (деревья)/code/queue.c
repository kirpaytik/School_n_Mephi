#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define OK 0
#define BAD 1

typedef struct QueueList {
	QueueNode node;
	struct QueueList* next;
} QueueList;

typedef struct Queue {
	QueueList* head;
	QueueList* tail;
} Queue;

short q_create(Queue** dest)
{
	Queue* que = (Queue*)malloc(sizeof(Queue));
	if (!que) {
		printf("Memory allocation error!\n");
		return BAD;
	}
	*que = (Queue){NULL, NULL};
	*dest = que;
	return OK;
}


void q_free(Queue* que)
{
	QueueList *ptr = que->head, *next;
	que->head = NULL;
	while (ptr) {
		free(ptr->node.prefix);
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
	que->tail = NULL;
}


short q_insert(Queue* que, Node* treeNode, int level, char* prefix)
{
	QueueList* new = (QueueList*)malloc(sizeof(QueueList));
	if (!new) {
		printf("Memory allocation error!\n");
		return BAD;
	}
	char* newprefix = strdup(prefix);
	if (!newprefix) {
		free(new);
		printf("Memory allocation error!\n");
		return BAD;
	}
	QueueNode node = (QueueNode){treeNode, level, newprefix};
	*new = (QueueList){node, NULL};
	if (que->tail)
		que->tail->next = new;
	else
		que->head = new;
	que->tail = new;
	return OK;
}


short q_delete(Queue* que, QueueNode* dest)
{
	if (q_is_empty(que))
		return -1;

	QueueList* temp = que->head;
	que->head = que->head->next;
	if (!que->head)
		que->tail = NULL;

	*dest = temp->node;
	temp->next = NULL;
	free(temp);
	return OK;
}


short q_is_empty(Queue* que)
{
	return que->tail == NULL;
}

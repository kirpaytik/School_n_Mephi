#ifndef QUEUE_H
#define QUEUE_H

#include "tree.h"

typedef struct QueueNode {
	Node* treeNode;
	int level;
	char* prefix;
} QueueNode;

typedef struct Queue Queue;

short q_create(Queue** dest);
void q_free(Queue* que);
short q_insert(Queue* que, Node* treeNode, int level, char* prefix);
short q_delete(Queue* que, QueueNode* dest);

short q_is_empty(Queue* que);

#endif

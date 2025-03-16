#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "graph.h"

typedef struct QueueNode {
	Vertex* vertex;
	struct QueueNode* next;
} QueueNode;

typedef struct Queue Queue;

Queue* q_create();
void q_free(Queue* que);
void q_push(Queue* que, Vertex* vertex);
Vertex* q_pop(Queue* queue);

bool q_is_empty(Queue* que);

#endif

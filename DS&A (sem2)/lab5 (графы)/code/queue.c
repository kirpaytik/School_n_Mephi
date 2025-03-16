#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define OK 0

struct Queue {
	QueueNode* head;
	QueueNode* tail;
};


Queue* q_create()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}


void q_free(Queue* queue)
{
    while (!q_is_empty(queue))
        q_pop(queue);
}


void q_push(Queue* queue, Vertex* vertex)
{
    QueueNode* new = (QueueNode*)malloc(sizeof(QueueNode));
    new->vertex = vertex;
    new->next = NULL;

    if (queue->head == NULL)
        queue->head = new;
    else
        queue->tail->next = new;
    queue->tail = new;
}


Vertex* q_pop(Queue* queue)
{
    if (q_is_empty(queue)) {
        return NULL;
    }

    QueueNode* temp = queue->head;
    Vertex* vertex = temp->vertex;
    queue->head = queue->head->next;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    free(temp);
    return vertex;
}


bool q_is_empty(Queue* queue) {
    return queue->head == NULL;
}

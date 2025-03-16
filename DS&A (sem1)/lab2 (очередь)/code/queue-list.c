#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct Queue {
	Passanger *head;
	Passanger *tail;
} Queue;


void free_queue(QueuePtr *que)
{
	if (*que == NULL) {
		return;
	}
	Passanger *ptr = (*que)->head;
	Passanger *next;
	while (ptr != NULL) {
		next = ptr->next;
		free_passanger(ptr);
		free(ptr);
		ptr = next;
	}
	(*que)->head = NULL;
	(*que)->tail = NULL;
	free(*que);
	*que = NULL;
}


QueuePtr create_queue(int size)
{
	size = size; // unused bcs needed in queue-vector.c, but not here
	QueuePtr que = NULL;
	que = (QueuePtr)malloc(sizeof(Queue));
	if (que == NULL) {
		printf("Не найдено свободной памяти\n");
		return NULL;
	}
	que->tail = NULL;
	que->head = NULL;
	return que;
}


void printf_queue(QueuePtr que)
{
	Passanger *ptr = que->head;
	while (ptr != NULL) {
		printf_passanger(*ptr);
		printf(" ");
		ptr = ptr->next;
	}
	printf("\n");
}


void printf_task_queue(QueuePtr que)
{
	Passanger *ptr = que->head;
	while (ptr != NULL) {
		printf("%s ", ptr->id);
		ptr = ptr->next;
	}
}


int insert_queue(QueuePtr que, Passanger pass)
{
	Passanger *new = (Passanger*)malloc(sizeof(Passanger));
	if (new == NULL) {
		printf("Не найдено свободной памяти!\n");
		return 0;
	}
	*new = passanger_copy(pass);
	if (new->id == NULL) {
		free(new);
		return 0;
	}
	new->next = NULL;
	if (que->head == NULL) {
		que->head = new;
	}
	else {
		que->tail->next = new;
	}
	que->tail = new;
	return 1;
}


void pop_queue(QueuePtr que)
{
	Passanger *pass = que->head;
	que->head = que->head->next;
	free_passanger(pass);
	free(pass);
}


Passanger get_queue(QueuePtr que, int index)
{
	Passanger *ptr = que->head;
	int i = 0;
	while (ptr != NULL) {
		if (i == index) {
			return *ptr;
		}
		ptr = ptr->next;
		i++;
	}
	return (Passanger){NULL, 0, 0, 0, NULL};
}


Passanger get_queue_first(QueuePtr que)
{
	return *(que->head);
}


Passanger get_queue_last(QueuePtr que)
{
	return *(que->tail);
}


int queue_length(QueuePtr que)
{
	Passanger *ptr = que->head;
	int len = 0;
	while (ptr != NULL) {
		len++;
		ptr = ptr->next;
	}
	return len;
}


int queue_is_empty(QueuePtr que)
{
	if (que->head == NULL) {
		return 1;
	}
	return 0;
}


int queue_is_full(QueuePtr que)
{
	que = que;
	// т.к по условию очередь на листе не переполняется
	return 0;
}

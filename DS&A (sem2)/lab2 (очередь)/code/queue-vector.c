#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

typedef struct Queue {
	int head;
	int tail;
	int size;
	int len;
	Passanger *arr;
} Queue;


void free_queue(QueuePtr *que)
{
	if (*que == NULL) {
		return;
	}
	if ((*que)->arr == NULL) {
		free(*que);
		*que = NULL;
		return;
	}
	int i;
	for (i = 0; i < (*que)->size; i++) {
		free_passanger((*que)->arr + i);
	}
	free((*que)->arr);
	free(*que);
	*que = NULL;
}


QueuePtr create_queue(int size)
{
	if (size < 1) {
		printf("Невозможно создать очередь: введена неверная длина!\n");
		return NULL;
	}
	QueuePtr que = (QueuePtr)malloc(sizeof(Queue));;
	if (que == NULL) {
		printf("Не найдено свободной памяти\n");
		return NULL;
	}
	que->tail = 0;
	que->head = 0;
	que->len = 0;
	que->arr = (Passanger*)calloc(size, sizeof(Passanger));
	if (que->arr == NULL) {
		printf("Не найдено свободной памяти\n");
		free(que);
		return NULL;
	}
	que->size = size;
	return que;
}


void printf_queue(QueuePtr que)
{
	int p;
	for (p = que->head; p != que->tail; p = (p+1) % que->size) {
		printf_passanger(que->arr[p]);
		printf(" ");
	}
}


void printf_task_queue(QueuePtr que)
{
	int p;
	int flag = queue_is_full(que);
	for (p = que->head; p != que->tail || flag == 1; p = (p+1) % que->size) {
		flag = 0;
		printf("%s ", que->arr[p].id);
	}
}


int insert_queue(QueuePtr que, Passanger pass)
{
	if (queue_is_full(que) == 1) {
		printf("Ошибка: очередь полна!\n");
		return 0;
	}
	Passanger pass_copy = passanger_copy(pass);
	if (pass_copy.id == NULL) {
		return 0;
	}
	que->arr[que->tail] = pass_copy;
	que->tail = (que->tail + 1) % que->size;
	que->len++;
	return 1;
}


void pop_queue(QueuePtr que)
{
	free_passanger(que->arr + que->head);
	que->head = (que->head + 1) % que->size;
	que->len--;
}


Passanger get_queue(QueuePtr que, int index)
{
	int p, i = 0, flag = 0;
	if (queue_is_full(que) == 1) {
		flag = 1;
	}
	for (p = que->head; p != que->tail || flag == 1; p = (p+1) % que->size) {
		flag = 0;
		if (i == index) {
			return que->arr[p];
		}
		i++;
	}
	return (Passanger){NULL, 0, 0, 0, NULL};
}


Passanger get_queue_first(QueuePtr que)
{
	return que->arr[0];
}


Passanger get_queue_last(QueuePtr que)
{
	int indx = (que->tail - 1 + que->size) % que->size;
	return que->arr[indx];
}


int queue_length(QueuePtr que)
{
	return que->len;
}


int queue_is_empty(QueuePtr que)
{
	if (que->len == 0) {
		return 1;
	}
	return 0;
}


int queue_is_full(QueuePtr que)
{
	if (que->head == que->tail && que->len > 0) {
		return 1;
	}
	return 0;
}

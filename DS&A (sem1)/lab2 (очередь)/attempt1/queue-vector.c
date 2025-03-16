#include <stdio.h>
#include <stdlib.h>
#include "mylibrary.h"

typedef struct Queue {
	int head;
	int tail;
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
	int length = queue_length(*que);
	for (i = 0; i < length; i++) {
		free_passanger((*que)->arr + i);
	}
	free((*que)->arr);
	free(*que);
	*que = NULL;
}


QueuePtr create_queue()
{
	QueuePtr que = (QueuePtr)malloc(sizeof(Queue));;
	if (que == NULL) {
		printf("Не найдено свободной памяти\n");
		return NULL;
	}
	que->tail = 0;
	que->head = 0;
	que->arr = (Passanger*)malloc(sizeof(Passanger));
	if (que->arr == NULL) {
		printf("Не найдено свободной памяти\n");
		free(que);
		return NULL;
	}
	return que;
}


void printf_queue(QueuePtr que)
{
	int p;
	for (p = que->head; p < que->tail; p++) {
		printf_passanger(que->arr[p]);
		printf(" ");
	}
}


int queue_push_back(QueuePtr que, Passanger pass)
{
	Passanger *temp = (Passanger*)realloc(que->arr, (que->tail + 1) * sizeof(Passanger));
	if (temp == NULL) {
		printf("Не найдено свободной памяти\n");
		return 0;
	}
	que->arr = temp;
	que->arr[que->tail] = passanger_copy(pass);
	que->tail++;
	return 1;
}


int queue_length(QueuePtr que)
{
	return que->tail - que->head;
}


int queue_is_active(QueuePtr que, int time_cur)
{
	int tin, tout;
	int p;
	Passanger pass;
	for (p = que->head; p < que->tail; p++) {
		pass = que->arr[p];
		tin = pass.tin;
		tout = tin + pass.ts - 1; // -1, т.к
		// если приехал в 1 и был 5 сек, то ушёл в 5ю секунду
		if (tin <= time_cur && time_cur <= tout) {
			return 1;
		}
	}
	return 0;
}


int queue_ppl_count(QueuePtr que, int time_cur)
{
	int ppl = 0;
	int p;
	Passanger pass;
	for (p = que->head; p < que->tail; p++) {
		pass = que->arr[p];
		if (pass.tin >= time_cur) {
			break;
		}
		ppl++;
	}
	return ppl;
}


int queue_time_count(QueuePtr que, int time_cur)
{
	int q_time = 0, time_in, time_out;
	int t, p;
	Passanger pass;
	for (t = 0; t < time_cur+1; t++) {
		for (p = que->head; p < que->tail; p++) {
			pass = que->arr[p];
			time_in = pass.tin;
			time_out = time_in + pass.ts;
			if (time_in < t && t <= time_out) {
				q_time++;
				break;
			}
		}
	}
	return q_time;
}


int queue_get_timein(QueuePtr que, int time_arrive)
{
	if (que->tail == que->head) {
		return time_arrive;
	}
	Passanger pass = que->arr[que->tail - 1];
	// -1, потому что если пришёл в 1ю сек и занял одну сек, то 2я сек уже свободна
	int time_last_out = pass.tin + pass.ts - 1;
	// но time_last_out + 1 - когда можно пихать нового
	if (time_arrive < time_last_out + 1) {
		return time_last_out + 1;
	}
	return time_arrive;
}


int queue_set_time_changes(QueuePtr que, int **arr, int *len)
{
	int p;
	int *temp;
	Passanger pass;
	for (p = que->head; p < que->tail; p++) {
		pass = que->arr[p];
		temp = (int*)realloc(*arr, (*len + 2) * sizeof(int));
		if (temp == NULL) {
			printf("Не найдено свободной памяти\n");
			return 0;
		}
		*arr = temp;
		(*arr)[*len] = pass.ta;
		(*len)++;
		(*arr)[*len] = pass.tin + pass.ts;
		(*len)++;
	}
	return 1;
}


void printf_timed_queue(QueuePtr que, int time_cur)
{
	int p;
	int flag = 0;
	Passanger pass;
	for (p = que->head; p < que->tail; p++) {
		pass = que->arr[p];
		if (pass.tin + pass.ts <= time_cur) {
			continue;
		}
		if (time_cur < pass.ta) {
			break;
		}
		flag = 1;
		printf("%s ", pass.id);
	}
	if (flag == 0) {
		printf("---");
	}
}

#include <stdio.h>
#include <stdlib.h>
#include "mylibrary.h"

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
		ptr = next;
	}
	(*que)->head = NULL;
	(*que)->tail = NULL;
	free(*que);
	*que = NULL;
}


QueuePtr create_queue()
{
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
	while (ptr != que->tail) {
		printf_passanger(*ptr);
		printf(" ");
		ptr = ptr->next;
	}
	printf_passanger(*ptr);
	printf("\n");
}


int queue_push_back (QueuePtr que, Passanger pass)
{
	Passanger *new = (Passanger*)malloc(sizeof(Passanger));
	if (new == NULL) {
		printf("Не найдено свободной памяти\n");
		return 0;
	}
	*new = pass;
	if (queue_length(que) == 0) {
		que->head = new;
	}
	else {
		que->tail->next = new;
	}
	que->tail = new;
	return 1;
}


int queue_length(QueuePtr que)
{
	if (que->head == NULL) {
		return 0;
	}
	Passanger *ptr = que->head;
	int len = 0;
	while (ptr != que->tail) {
		len++;
		ptr = ptr->next;
	}
	return len + 1;
}


int queue_is_active(QueuePtr que, int time_cur)
{
	int tin, tout;
	Passanger *ptr = que->head;
	while (ptr != NULL) {
		tin = ptr->tin;
		tout = tin + ptr->ts - 1;
		if (tin <= time_cur && time_cur <= tout) {
			return 1;
		}
		ptr = ptr->next;
	}
	return 0;
}


int queue_ppl_count(QueuePtr que, int time_cur)
{
	int ppl = 0;
	 Passanger *ptr = que->head;
	 while(ptr != NULL) {
	 	if (ptr->tin >= time_cur) {
	 		break;
	 	}
	 	ppl++;
	 	ptr = ptr->next;
	 }
	 return ppl;
}


int queue_time_count(QueuePtr que, int time_cur)
{

	int q_time = 0, time_in, time_out;
	int t;
	Passanger *ptr = que->head;
	for (t = 0; t < time_cur+1; t++) {
		ptr = que->head;
		while (ptr != NULL) {
			time_in = ptr->tin;
			time_out = time_in + ptr->ts;
			if (time_in < t && t <= time_out) {
				q_time++;
				break;
			}
			ptr = ptr->next;
		}
	}
	return q_time;
}


int queue_get_timein(QueuePtr que, int time_arrive)
{
	if (queue_length(que) == 0) {
		return time_arrive;
	}
	Passanger pass = *(que->tail);
	int time_last_out = pass.tin + pass.ts - 1;
	if (time_arrive < time_last_out + 1) {
		return time_last_out + 1;
	}
	return time_arrive;
}


int queue_set_time_changes(QueuePtr que, int **arr, int *len)
{
	int *temp;
	Passanger *ptr = que->head;
	while (ptr != NULL) {
		temp = (int*)realloc(*arr, (*len + 2) * sizeof(int));
		if (temp == NULL) {
			printf("Не найдено свободной памяти\n");
			return 0;
		}
		*arr = temp;
		(*arr)[*len] = ptr->ta;
		(*len)++;
		(*arr)[*len] = ptr->tin + ptr->ts;
		(*len)++;
		ptr = ptr->next;
	}
	return 1;
}


void printf_timed_queue(QueuePtr que, int time_cur)
{
	int flag = 0;
	Passanger *ptr = que->head;
	while (ptr != NULL) {
		if (ptr->tin + ptr->ts <= time_cur) {
			ptr = ptr->next;
			continue;
		}
		if (time_cur < ptr->ta) {
			break;
		}
		flag = 1;
		printf("%s ", ptr->id);
		ptr = ptr->next;
	}
	if (flag == 0) {
		printf("---");
	}
}

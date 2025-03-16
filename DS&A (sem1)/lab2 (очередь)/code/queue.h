#ifndef QUEUE_H
#define QUEUE_H

#include "mylib.h"

QueuePtr create_queue(int size);
void free_queue(QueuePtr *que);
void printf_queue(QueuePtr que);
void printf_task_queue(QueuePtr que);

int insert_queue(QueuePtr que, Passanger pass);
Passanger get_queue(QueuePtr que, int index);
void pop_queue(QueuePtr que);

Passanger get_queue_first(QueuePtr que);
Passanger get_queue_last(QueuePtr que);
int queue_length(QueuePtr que);
int queue_is_empty(QueuePtr que);
int queue_is_full(QueuePtr que);

#endif

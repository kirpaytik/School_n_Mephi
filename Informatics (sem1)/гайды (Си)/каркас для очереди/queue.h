#ifndef QUEUE_H
#define QUEUE_H

#include "mylib.h"

struct Queue {
    int size;
    int *arr;
    int head;
    int tail;
};

int q_push(Queue *que, int value);
int q_get(Queue que, int *dest);
int q_rem(Queue *que);

int q_length(Queue que);
int q_is_empty(Queue que);

#endif

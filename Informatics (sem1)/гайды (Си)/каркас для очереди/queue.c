#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

#define OK 0
#define BAD 1


int q_create(Queue **dest)
{
    Queue *que = (Queue*)malloc(sizeof(Queue));
    *que = (Queue){0, NULL, 0, 0};
    que->arr = (int*)malloc(sizeof(int));
    que->arr[0] = -7;
    if (!que->arr) {
        printf("Memory allocation error\n");
        printf("(allocation memory for queue array)\n");
        return BAD;
    }
    *dest = que;
    return OK;
}


void q_free(Queue *que)
{
    free(que->arr);
    que->size = 0;
    que->head = 0;
    que->tail = 0;
}


void q_print(Queue que)
{
    if (q_is_empty(que)) {
        printf("The queue is empty!\n");
        return;
    }
    int i;
    for (i = que.head; i < que.tail - 1; i++) {
        printf("%d ", que.arr[i]);
    }
    printf("%d\n", que.arr[i]);
}


int q_push(Queue *que, int value)
{
    int *temp = (int*)realloc(que->arr, (que->size + 1) * sizeof(int));
    if (!temp) {
        printf("Memory allocation error\n");
        printf("(reallocating queue to extend it)\n");
        return BAD;
    }
    que->arr = temp;
    que->size++;
    que->arr[que->tail] = value;
    que->tail++;
    return OK;
}


int q_get(Queue que, int *dest)
{
    *dest = que.arr[que.head];
    return OK;
}


int q_rem(Queue *que)
{
    que->head++;
    return OK;
}


int q_length(Queue que)
{
    return que.tail - que.head;
}


int q_is_empty(Queue que)
{
    return que.tail == que.head;
}

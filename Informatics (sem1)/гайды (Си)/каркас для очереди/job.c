#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

#define OK 0
#define BAD 1

void endofprog(Queue *que)
{
    q_free(que);
    free(que);
}


int job_fill(Queue *que, int size, int *values)
{
    int returned;
    int i;
    for (i = 0; i < size; i++) {
        returned = q_push(que, values[i]);
        if (returned) {
            printf("Pushing error\n");
            printf("(value №%d", i);
            return BAD;
        }
    }
    return OK;
}


int job_insert(Queue *que, int value)
{
    int returned = q_push(que, value);
    if (returned) {
        printf("Pushing error\n");
        return BAD;
    }
    return OK;
}


int job_delete(Queue *que)
{
    int returned = q_rem(que);
    if (returned) {
        printf("Removal error");
        return BAD;
    }
    return OK;
}


int job_clear(Queue *que)
{
    int returned;
    int i = 0;
    while (!q_is_empty(*que)) {
        returned = q_rem(que);
        if (returned) {
            printf("Removal error");
            printf("(removing element №%d)\n", i);
            return BAD;
        }
        i++;
    }
    return OK;
}


void job_print(Queue *que)
{
    q_print(*que);
}

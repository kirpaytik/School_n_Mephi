#ifndef MYLIB_H
#define MYLIB_H

// structure queue
typedef struct Queue Queue;
int q_create(Queue **dest);
void q_free(Queue *que);
void q_print(Queue que);

// dialogue.c
int dialogue(Queue *que);
int dialogue_menu(Queue *que, int panel);
int dialogue_fill(Queue *que);
int dialogue_insert(Queue *que);

// job.c
void endofprog(Queue *que);
int job_fill(Queue *que, int size, int *values);
int job_insert(Queue *que, int value);
int job_delete(Queue *que);
int job_clear(Queue *que);
void job_print(Queue *que);

#endif

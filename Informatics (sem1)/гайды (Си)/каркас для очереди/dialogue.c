#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

#define OK 0
#define BAD 1

int dialogue(Queue *que)
{
    int panel = 1;
    int returned, guard;
    while (panel) {
        printf("Choose an option from the list:\n\
                (1) Fill the queue with given values\n\
                (2) Insert a value into the queue\n\
                (3) Delete one element from the queue\n\
                (4) Clear all the queue\n\
                (5) Print the queue\n\
                (6) Finish the program\n>>> ");
        guard = scanf("%d", &panel);
        if (!guard) {
            printf("Inputting an integer value error\n");
            printf("(panel selecting a menu option)\n");
            return BAD;
        }
        if (panel == 6) {
            return OK;
        }
        returned = dialogue_menu(que, panel);
        if (returned) {
            printf("An error occured during chosen operation execution\n");
            return BAD;
        }
    }
    return OK;
}


int dialogue_menu(Queue *que, int panel)
{
    int returned;
    switch(panel) {
    case 1:
        returned = dialogue_fill(que);
        if (returned) {
            printf("Filling the queue (dialogue) error\n");
            return BAD;
        }
        printf("Outputing the queue\n");
        job_print(que);
        break;
    case 2:
        returned = dialogue_insert(que);
        if (returned) {
            printf("Inserting the value (dialogue) error\n");
            return BAD;
        }
        printf("Outputing the queue\n");
        job_print(que);
        break;
    case 3:
        printf("Deleting an element from the queue\n");
        returned = job_delete(que);
        if (returned) {
            printf("Deleting an element error\n");
            return BAD;
        }
        printf("Outputing the queue\n");
        job_print(que);
        break;
    case 4:
        printf("Clearing the queue\n");
        returned = job_clear(que);
        if (returned) {
            printf("Clearing the queue error\n");
            return BAD;
        }
        printf("Outputing the queue\n");
        job_print(que);
        break;
    case 5:
        printf("Outputing the queue\n");
        job_print(que);
        break;
    }
    return OK;
}


int dialogue_fill(Queue *que)
{
    printf("Input a number of values to fill:\n>>> ");
    int amount;
    int guard = scanf("%d", &amount);
    if (!guard) {
        printf("(number of values to fill)\n");
        return BAD;
    }
    int *values = (int*)malloc(amount * sizeof(int));
    if (!values) {
        printf("Memory allocation error\n");
        printf("(an array of values to fill)\n");
        return BAD;
    }
    int i;
    printf("Enter %d values to fill:\n>>> ", amount);
    for (i = 0; i < amount; i++) {
        guard = scanf("%d", values + i);
        if (!guard) {
            printf("Inputting an integer value error\n");
            printf("(value to fill №%d)\n", i);
            free(values);
            return BAD;
        }
    }
    printf("Filling the queue with given values\n");
    int returned = job_fill(que, amount, values);
    if (returned) {
        printf("Filling the queue (job) error\n");
        free(values);
        return BAD;
    }
    free(values);
    return OK;
}


int dialogue_insert(Queue *que)
{
    printf("Enter a value to insert:\n>>> ");
    int value;
    int guard = scanf("%d", &value);
    if (!guard) {
        printf("Inputting an integer value error\n");
        printf("(value to insert)\n");
        return BAD;
    }
    printf("Instering a value into the queue\n");
    int returned = job_insert(que, value);
    if (returned) {
        printf("Inserting a value (job) error\n");
        return BAD;
    }
    return OK;
}

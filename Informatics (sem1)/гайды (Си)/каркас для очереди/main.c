#include <stdio.h>
#include "mylib.h"
#include "queue.h"


int main()
{
    Queue *que;
    int returned = q_create(&que);
    if (returned) {
        printf("Creating Queue object error\n");
        printf("Terminating the program\n");
        endofprog(que);
        return 1;
    }
    
    returned = dialogue(que);
    if (returned) {
        printf("An error occured\n");
        printf("Terminating the program\n");
        endofprog(que);
        return 1;
    }
    
    printf("Successfully reached the end of program\n");
    endofprog(que);
    return 0;
}

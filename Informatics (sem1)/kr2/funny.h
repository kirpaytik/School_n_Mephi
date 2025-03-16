typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

void process1 (int**, int*);
char* process2 (char*);
void process3 (List*);
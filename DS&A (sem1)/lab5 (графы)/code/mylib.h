#ifndef MYLIB_H
#define MYLIB_H

#include <stdio.h> // для FILE*
#include <stdbool.h>

typedef struct KeySpace {
    char* key;
    unsigned int info;
} KeySpace;

typedef struct Graph Graph;

// dialog.c
short dialogue_menu(Graph* graph);
short dialog_switch(Graph* graph, int panel);

short dialog_fill_file(Graph* graph);
short dialog_fill_file_line(Graph* graph, char* line, FILE* file);
short dialog_print(Graph* graph);
short dialog_print_txtfile(Graph* graph);
short dialog_print_graphviz(Graph* graph);

short dialog_insert_vertex(Graph* graph);
short dialog_insert_edge(Graph* graph);
short dialog_delete_vertex(Graph* graph);
short dialog_delete_edge(Graph* graph);
short dialog_edit_vertex(Graph* graph);
short dialog_edit_edge(Graph* graph);

short dialog_traverse_bfs(Graph* graph);
short dialog_bellmanford(Graph* graph);
short dialog_floydwarshall(Graph* graph);


short dialog_get_file(FILE** file, char filemode[3]);


// input.c
short scanfIntType(int* target, FILE* file, short mode);
short scanfUIntType(unsigned int* target, FILE* file, short mode);
short scanfConsoleInt(int* target);
short scanfConsoleUInt(unsigned int* target);
short scanfTxtFileInt(int* target, FILE* file);
short scanfTxtFileUInt(unsigned int* target, FILE* file);
short scanfBinFileInt(int* target, FILE* file);
short scanfBinFileUInt(unsigned int* target, FILE* file);

short is_int_overflow(char s[13]);
short is_uint_overflow(char s[12]);

short readline(char** dest, FILE* file, short mode, bool empty_rule);
short readConsoleLine(char** dest, bool empty_rule);
short readTxtFileLine(char** dest, FILE* file, bool empty_rule);
short remove_end_spaces(char** dest);

short read_y_or_n(char* dest);
short read_int_inrange(void* dest, short type, int min, int max);


// job.c
Graph* create_graph();
void endofprog(Graph* graph);
short start_program(Graph* graph);

bool job_isfound_vertex(Graph* graph, char* room);
bool job_isfound_edge(Graph* graph, char* room1, char* room2);
void job_insert_vertex(Graph* graph, char* room, short type);
void job_insert_edge(Graph* graph, char* room1, char* room2, int length);
void job_delete_vertex(Graph* graph, char* room);
void job_delete_edge(Graph* graph, char* room1, char* room2);
void job_edit_vertex(Graph* graph, char* room, short type_new);
void job_edit_edge(Graph* graph, char* room1, char* room2, int length_new);

bool job_traverse_bfs(Graph* graph, char* room);
void job_bellmanford(Graph* graph, char* room1, char* room2);
void job_floydwarshall(Graph* graph, char* room);

void job_print_console(Graph* graph);
void job_print_txtfile(Graph* graph, FILE* file);
void job_print_graphviz(Graph* graph, FILE* file);

#endif
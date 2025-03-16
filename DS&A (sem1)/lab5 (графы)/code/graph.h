#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include "mylib.h"

typedef struct Vertex {
	char* room;
	short type;
	struct Edge** edges;
	unsigned int edge_count;

	short visited;
	int distance;
	struct Vertex* pred;
} Vertex;

typedef struct Edge {
	Vertex* in;
	Vertex* out;
	int length;
} Edge;

struct Graph {
	Vertex** vertices;
	unsigned int vertex_count;
};


// struct Graph
Graph* g_create();
void g_free(Graph* graph);
void g_print_console(Graph* graph);
void g_print_txtfile(Graph* graph, FILE* file);
Vertex* g_create_vertex(char* room, short type);
Edge* g_create_edge(Vertex* v_in, Vertex* v_out, int length);

void g_insert_vertex(Graph* graph, Vertex* new);
void g_insert_edge(Edge* new);
void g_delete_vertex(Graph* graph, Vertex* vertex);
void g_delete_edge(Edge* edge);
void g_edit_vertex(Vertex* vertex, short type_new);
void g_edit_edge(Edge* edge, int length_new);
Vertex* g_find_vertex(Graph* graph, char* room);
Edge* g_find_edge(Graph* graph, char* room1, char* room2);

bool g_vertex_isExitReachable_bfs(Graph* graph, Vertex* start);
void g_bellman_ford(Graph* graph, Vertex* start, Vertex* end);
void g_bellman_print_path(Vertex* end, Vertex* start);
void g_floyd_find_exit(Graph* graph, Vertex* start);
void g_floyd_warshall(Graph* graph, int*** dist_dest, int*** next_dest);
void g_floyd_print_path(Graph* graph, int** next, int start, int end);

bool g_is_empty(Graph* graph);

// visual.c - for graphviz
void generateDot(Graph* graph, FILE* file);
void print_node_dot(Graph* graph, FILE* file);

#endif
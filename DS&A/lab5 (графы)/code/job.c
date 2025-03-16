#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "graph.h"

#define OK 0


Graph* create_graph()
{
	return g_create();
}


void endofprog(Graph* graph)
{
	g_free(graph);
	free(graph);
}


short start_program(Graph* graph)
{
	short checker = dialogue_menu(graph);
	return checker;
}


bool job_isfound_vertex(Graph* graph, char* room)
{
	return g_find_vertex(graph, room) != NULL;
}


bool job_isfound_edge(Graph* graph, char* room1, char* room2)
{
	return g_find_edge(graph, room1, room2) != NULL;
}


void job_insert_vertex(Graph* graph, char* room, short type)
{
	Vertex* vertex = g_create_vertex(room, type);
	g_insert_vertex(graph, vertex);
}


void job_insert_edge(Graph* graph, char* room1, char* room2, int length)
{
	Vertex* v1 = g_find_vertex(graph, room1);
	Vertex* v2 = g_find_vertex(graph, room2);
	Edge* edge = g_create_edge(v1, v2, length);
	g_insert_edge(edge);
}


void job_delete_vertex(Graph* graph, char* room)
{
	Vertex* vertex = g_find_vertex(graph, room);
	g_delete_vertex(graph, vertex);
}


void job_delete_edge(Graph* graph, char* room1, char* room2)
{
	Edge* edge = g_find_edge(graph, room1, room2);
	g_delete_edge(edge);
}


void job_edit_vertex(Graph* graph, char* room, short type_new)
{
	Vertex* vertex = g_find_vertex(graph, room);
	g_edit_vertex(vertex, type_new);
}


void job_edit_edge(Graph* graph, char* room1, char* room2, int length_new)
{
	Edge* edge = g_find_edge(graph, room1, room2);
	g_edit_edge(edge, length_new);
}


bool job_traverse_bfs(Graph* graph, char* room)
{
	Vertex* vertex = g_find_vertex(graph, room);
	return g_vertex_isExitReachable_bfs(graph, vertex);
}


void job_bellmanford(Graph* graph, char* room1, char* room2)
{
	Vertex* v1 = g_find_vertex(graph, room1);
	Vertex* v2 = g_find_vertex(graph, room2);
	g_bellman_ford(graph, v1, v2);
}


void job_floydwarshall(Graph* graph, char* room)
{
	Vertex* vertex = g_find_vertex(graph, room);
	g_floyd_find_exit(graph, vertex);
}


void job_print_console(Graph* graph)
{
	g_print_console(graph);
}


void job_print_txtfile(Graph* graph, FILE* file)
{
	g_print_txtfile(graph, file);
}


void job_print_graphviz(Graph* graph, FILE* file)
{
	generateDot(graph, file);
}

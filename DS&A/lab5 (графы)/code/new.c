#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "graph.h"

int main()
{
	Graph* graph = g_create();
	start_program(graph);
	end_program(graph);

	return 0;
}


void start_program(Graph* graph)
{
	while (1) {
		printf("1 - insert vertex\n");
		printf("2 - insert edge\n");
		printf("3 - delete vertex\n");
		printf("4 - delete edge\n");
		printf("5 - edit vertex\n");
		printf("6 - edit edge\n");
		printf("7 - print the graph\n");
		printf("8 - traverse (isExitReachable_bfs)\n");
		printf("9 - bellman-ford\n");
		printf("10 - floyd-warshall\n");
		int menu;
		printf(">>> ");
		int guard = scanf("%d%*c", &menu);
		if (guard == EOF) return;
		switch (menu) {
		case 1:
			job_iv(graph);
			break;
		case 2:
			job_ie(graph);
			break;
		case 3:
			job_dv(graph);
			break;
		case 4:
			job_de(graph);
			break;
		case 5:
			job_ev(graph);
			break;
		case 6:
			job_ee(graph);
			break;
		case 7:
			job_printg(graph);
			break;
		case 8:
			job_traverse_bfs(graph);
			break;
		case 9:
			job_bellmanford(graph);
			break;
		case 10:
			job_floydwarshall(graph);
			break;
		}
	}
}


void job_iv(Graph* graph)
{
	char* room = (char*)malloc(3 * sizeof(char));
	printf("room please\n>>> ");
	scanf("%c%*c", room);
	room[1] = room[0]; room[2] = '\0';

	short type;
	printf("type please\n>>> ");
	scanf("%hd%*c", &type);

	Vertex* vertex = g_create_vertex(room, type);
	free(room);
	g_insert_vertex(graph, vertex);
}


void job_ie(Graph* graph)
{
	char* room1 = (char*)malloc(3 * sizeof(char));
	printf("room1 please\n>>> ");
	scanf("%c%*c", room1);
	room1[1] = room1[0]; room1[2] = '\0';

	Vertex* v_in = g_find_vertex(graph, room1);
	free(room1);
	if (!v_in) {
		printf("room1 was not found!\n");
		return;
	}

	char* room2 = (char*)malloc(3 * sizeof(char));
	printf("room2 please\n>>> ");
	scanf("%c%*c", room2);
	room2[1] = room2[0]; room2[2] = '\0';

	Vertex* v_out = g_find_vertex(graph, room2);
	free(room2);
	if (!v_out) {
		printf("room2 was not found!\n");
		return;
	}

	int length;
	printf("length please\n>>> ");
	scanf("%d%*c", &length);

	Edge* edge = g_create_edge(v_in, v_out, length);

	g_insert_edge(graph, edge);
}


void job_dv(Graph* graph)
{
	char* room = (char*)malloc(3 * sizeof(char));
	printf("room please\n>>> ");
	scanf("%c%*c", room);
	room[1] = room[0]; room[2] = '\0';

	Vertex* vertex = g_find_vertex(graph, room);
	free(room);
	if (!vertex) {
		printf("vertex to delete was not found!\n");
		return;
	}

	g_delete_vertex(graph, vertex);
}


void job_de(Graph* graph)
{
	char* room1 = (char*)malloc(3 * sizeof(char));
	printf("room1 please\n>>> ");
	scanf("%c%*c", room1);
	room1[1] = room1[0]; room1[2] = '\0';

	char* room2 = (char*)malloc(3 * sizeof(char));
	printf("room2 please\n>>> ");
	scanf("%c%*c", room2);
	room2[1] = room2[0]; room2[2] = '\0';

	Edge* edge = g_find_edge(graph, room1, room2);
	free(room1);
	free(room2);
	if (!edge) {
		printf("edge to delete was not found!\n");
		return;
	}

	delete_edge(graph, edge);
}


void job_ev(Graph* graph)
{
	char* room = (char*)malloc(3 * sizeof(char));
	printf("room please\n>>> ");
	scanf("%c%*c", room);
	room[1] = room[0]; room[2] = '\0';

	Vertex* vertex = g_find_vertex(graph, room);
	free(room);
	if (!vertex) {
		printf("vertex to edit was not found!\n");
		return;
	}

	char* room_new = (char*)malloc(3 * sizeof(char));
	printf("room_new please\n>>> ");
	scanf("%c%*c", room_new);
	room_new[1] = room_new[0]; room_new[2] = '\0';

	short type_new;
	printf("type_new please\n>>> ");
	scanf("%hd%*c", &type_new);

	edit_vertex(vertex, room_new, type_new);
	free(room_new);
}


void job_ee(Graph* graph)
{
	char* room1 = (char*)malloc(3 * sizeof(char));
	printf("room1 please\n>>> ");
	scanf("%c%*c", room1);
	room1[1] = room1[0]; room1[2] = '\0';

	char* room2 = (char*)malloc(3 * sizeof(char));
	printf("room2 please\n>>> ");
	scanf("%c%*c", room2);
	room2[1] = room2[0]; room2[2] = '\0';

	Edge* edge = g_find_edge(graph, room1, room2);
	free(room1);
	free(room2);
	if (!edge) {
		printf("edge to edit was not found!\n");
		return;
	}

	int length_new;
	printf("length_new please\n>>> ");
	scanf("%d%*c", &length_new);

	edit_edge(edge, length_new);
}


void end_program(Graph* graph)
{
	g_free(graph);
	free(graph);
}


void job_printg(Graph* graph)
{
	g_print_console(graph);
}


void job_traverse_bfs(Graph* graph)
{
	char* room = (char*)malloc(3 * sizeof(char));
	printf("room please\n>>> ");
	scanf("%c%*c", room);
	room[1] = room[0]; room[2] = '\0';

	Vertex* vertex = g_find_vertex(graph, room);
	free(room);
	if (!vertex) {
		printf("vertex to start traversal was not found!\n");
		return;
	}

	bool is = g_vertex_isExitReachable_bfs(graph, vertex);
	if (is)
		printf("Yes, you can get to the exit from this vertex\n");
	else
		printf("Oops, the maze just maaayy be impossible to solve from this vertex\n");
}


void job_bellmanford(Graph* graph)
{
	char* room1 = (char*)malloc(3 * sizeof(char));
	printf("room1 please\n>>> ");
	scanf("%c%*c", room1);
	room1[1] = room1[0]; room1[2] = '\0';

	Vertex* v_in = g_find_vertex(graph, room1);
	free(room1);
	if (!v_in) {
		printf("room1 was not found!\n");
		return;
	}

	char* room2 = (char*)malloc(3 * sizeof(char));
	printf("room2 please\n>>> ");
	scanf("%c%*c", room2);
	room2[1] = room2[0]; room2[2] = '\0';

	Vertex* v_out = g_find_vertex(graph, room2);
	free(room2);
	if (!v_out) {
		printf("room2 was not found!\n");
		return;
	}

	bellman_ford(graph, v_in, v_out);
}


void job_floydwarshall(Graph* graph)
{
	char* room = (char*)malloc(3 * sizeof(char));
	printf("room please\n>>> ");
	scanf("%c%*c", room);
	room[1] = room[0]; room[2] = '\0';

	Vertex* vertex = g_find_vertex(graph, room);
	free(room);
	if (!vertex) {
		printf("vertex to start the maze was not found!\n");
		return;
	}

	floyd_find_exit(graph, vertex);
}

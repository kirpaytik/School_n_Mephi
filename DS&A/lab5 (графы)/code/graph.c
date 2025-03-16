#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "graph.h"
#include "queue.h"

#define ROOM_EXIT -1
#define ROOM_ENTRANCE 1

#define INF INT_MAX


Graph* g_create()
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->vertices = NULL;
	graph->vertex_count = 0;
	return graph;
}


void g_free(Graph* graph)
{
	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		Vertex* vertex = graph->vertices[i];

		for (unsigned int j = 0; j < vertex->edge_count; j++) {
			Edge* edge = vertex->edges[j];
			Vertex* other_vertex = (edge->in == vertex) ? edge->out : edge->in;
			if (!other_vertex)
				free(edge);
			else {
				int side = (edge->in == vertex) ? 1 : 0;
				if (side) edge->in = NULL;
				else edge->out = NULL;
			}
		}

		free(vertex->edges);
		free(vertex->room);
		free(vertex);
	}

	free(graph->vertices);
	graph->vertex_count = 0;
}



void g_print_console(Graph* graph)
{
	if (g_is_empty(graph)) {
		printf("The graph is empty!\n");
		return;
	}

	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		Vertex* vertex = graph->vertices[i];
		printf("%s", vertex->room);
		int fl = 0;

		for (unsigned int j = 0; j < vertex->edge_count; j++) {
			Edge* edge = vertex->edges[j];

			if (edge->in == vertex) {
				if (fl == 0) {
					printf(" -> ");
					fl = 1;
				}
				printf("%s", edge->out->room);
				if (j < vertex->edge_count - 1) {
					printf(", ");
				}
			}
		}
		printf("; type=%hd\n", vertex->type);
	}
}

void g_print_txtfile(Graph* graph, FILE* file)
{
	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		Vertex* vertex = graph->vertices[i];
		fprintf(file, "%s\n", vertex->room);
		fprintf(file, "%hd\n", vertex->type);
	}

	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		Vertex* vertex = graph->vertices[i];

		for (unsigned int j = 0; j < vertex->edge_count; j++) {
			Edge* edge = vertex->edges[j];

			if (edge->in == vertex) {
				fprintf(file, "%s -> %s\n", edge->in->room, edge->out->room);
				fprintf(file, "%d\n", edge->length);
			}
		}
	}
}


Vertex* g_create_vertex(char* room, short type)
{
	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
	vertex->room = strdup(room);
	vertex->type = type;
	vertex->edges = NULL;
	vertex->edge_count = 0;

	vertex->visited = 0;
	vertex->distance = INF;
	vertex->pred = NULL;
	return vertex;
}


Edge* g_create_edge(Vertex* vin, Vertex* vout, int length)
{
	Edge* edge = (Edge*)malloc(sizeof(Edge));
	edge->in = vin;
	edge->out = vout;
	edge->length = length;
	return edge;
}


void g_insert_vertex(Graph* graph, Vertex* new)
{
	graph->vertices = (Vertex**)realloc(graph->vertices, (graph->vertex_count + 1) * sizeof(Vertex*));
	graph->vertices[graph->vertex_count] = new;
	graph->vertex_count++;
}


void g_insert_edge(Edge* new)
{
	new->in->edges = (Edge**)realloc(new->in->edges, (new->in->edge_count + 1) * sizeof(Edge*));
	new->in->edges[new->in->edge_count] = new;
	new->in->edge_count++;

	new->out->edges = (Edge**)realloc(new->out->edges, (new->out->edge_count + 1) * sizeof(Edge*));
	new->out->edges[new->out->edge_count] = new;
	new->out->edge_count++;
}


void g_delete_vertex(Graph* graph, Vertex* vertex)
{
	for (unsigned int i = 0; i < vertex->edge_count; i++) {
		Edge* edge = vertex->edges[i];
		Vertex* other_vertex = (edge->in == vertex) ? edge->out : edge->in;

		for (unsigned int j = 0; j < other_vertex->edge_count; j++) {
			if (other_vertex->edges[j] == edge) {
				other_vertex->edges[j] = other_vertex->edges[other_vertex->edge_count - 1];
				other_vertex->edges = (Edge**)realloc(other_vertex->edges, (other_vertex->edge_count - 1) * sizeof(Edge*));
				other_vertex->edge_count--;
				break;
			}
		}
		free(edge);
	}

	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		if (graph->vertices[i] == vertex) {
			graph->vertices[i] = graph->vertices[graph->vertex_count - 1];
			break;
		}
	}
	graph->vertices = (Vertex**)realloc(graph->vertices, (graph->vertex_count - 1) * sizeof(Vertex*));
	graph->vertex_count--;

	free(vertex->edges);
	free(vertex->room);
	free(vertex);
}


void g_delete_edge(Edge* edge)
{
	Vertex* vin = edge->in;
	Vertex* vout = edge->out;

	for (unsigned int i = 0; i < vin->edge_count; i++) {
		if (vin->edges[i] == edge) {
			vin->edges[i] = vin->edges[vin->edge_count - 1];
			vin->edges = (Edge**)realloc(vin->edges, (vin->edge_count - 1) * sizeof(Edge*));
			vin->edge_count--;
			break;
		}
	}

	for (unsigned int i = 0; i < vout->edge_count; i++) {
		if (vout->edges[i] == edge) {
			vout->edges[i] = vout->edges[vout->edge_count - 1];
			vout->edges = (Edge**)realloc(vout->edges, (vout->edge_count - 1) * sizeof(Edge*));
			vout->edge_count--;
			break;
		}
	}

	free(edge);
}


void g_edit_vertex(Vertex* vertex, short type_new)
{
	vertex->type = type_new;
}


void g_edit_edge(Edge* edge, int length_new)
{
	edge->length = length_new;
}


Vertex* g_find_vertex(Graph* graph, char* room)
{
	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		if (strcmp(graph->vertices[i]->room, room) == 0) {
			return graph->vertices[i];
		}
	}
	return NULL;
}


Edge* g_find_edge(Graph* graph, char* room1, char* room2)
{
	Vertex* v1 = g_find_vertex(graph, room1);
	Vertex* v2 = g_find_vertex(graph, room2);
	if (!v1 || !v2) {
		return NULL;
	}

	for (unsigned int i = 0; i < v1->edge_count; i++) {
		if (v1->edges[i]->out == v2) {
			return v1->edges[i];
		}
	}

	return NULL;
}


bool g_vertex_isExitReachable_bfs(Graph* graph, Vertex* start)
{
	if (start->type == ROOM_EXIT) {
		printf("lol u r actually standing on exit rn bro...\n");
		return true;
	}

	bool fl = false;
	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		if (graph->vertices[i]->type == ROOM_EXIT) {
			fl = 1;
			break;
		}
	}
	if (!fl) {
		printf("NO EXITS IN THIS DAMN MAZE\n");
		return false;
	}

	if (start->edge_count == 0) {
		return false;
	}

	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		graph->vertices[i]->visited = 0;
	}
	Queue* queue = q_create();
	q_push(queue, start);
	start->visited = 1;

	while (!q_is_empty(queue)) {
		Vertex* current = q_pop(queue);

		for (unsigned int i = 0; i < current->edge_count; i++) {
			Vertex* neighbour = current->edges[i]->out;

			if (neighbour->type == -1) {
				q_free(queue);
				free(queue);
				return true;
			}

			if (!neighbour->visited) {
				neighbour->visited = 1;
				q_push(queue, neighbour);
			}
		}
	}

	q_free(queue);
	free(queue);
	return false;
}


void g_bellman_ford(Graph* graph, Vertex* start, Vertex* end)
{
	if (end->type != ROOM_EXIT) {
		printf("End vertex is not end-type!\n");
		return;
	}

	if (start == end) {
		printf("lol u r actually standing on exit rn bro...\n");
		return;
	}

	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		graph->vertices[i]->distance = INF;
		graph->vertices[i]->pred = NULL;
	}
	start->distance = 0;

	for (unsigned int i = 1; i <= graph->vertex_count - 1; i++)
	{
		for (unsigned int j = 0; j < graph->vertex_count; j++) {
			Vertex* u = graph->vertices[j];
			for (unsigned int k = 0; k < u->edge_count; k++) {
				Edge* edge = u->edges[k];
				Vertex* v = edge->out;

				if (u->distance < INF && u->distance + edge->length < v->distance) {
					v->distance = u->distance + edge->length;
					v->pred = u;
				}
			}
		}
	}

	for (unsigned int j = 0; j < graph->vertex_count; j++) {
		Vertex* u = graph->vertices[j];
		for (unsigned int k = 0; k < u->edge_count; k++) {
			Edge* edge = u->edges[k];
			Vertex* v = edge->out;

			if (u->distance < INF && u->distance + edge->length < v->distance) {
				printf("Graph contains a negative-weight cycle\n");
				return;
			}
		}
	}

	if (end->distance == INF) {
		printf("No path found from %s to %s\n", start->room, end->room);
		return;
	}
	printf("Shortest path from %s to %s: ", start->room, end->room);
	g_bellman_print_path(end, start);
	printf("\nTotal length: %d\n", end->distance);

	return;
}


void g_bellman_print_path(Vertex* end, Vertex* start)
{
	Vertex* current = end;
	Vertex *temp1, *temp2 = current->pred;
	end->pred = NULL;
	// разворачиваю пуьт
	while (current != start) {
		temp1 = current;
		current = temp2;
		temp2 = current->pred;
		current->pred = temp1;
	}
	while (current != end) {
		printf("%s -> ", current->room);
		current = current->pred;
	}
	printf("%s\n", end->room);
}


void g_floyd_find_exit(Graph* graph, Vertex* start)
{
	if (start->type == ROOM_EXIT) {
		printf("lol u r actually standing on exit rn bro...\n");
		return;
	}

	bool fl = false;
	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		if (graph->vertices[i]->type == ROOM_EXIT) {
			fl = 1;
			break;
		}
	}
	if (!fl) {
		printf("NO EXITS IN THIS DAMN MAZE\n");
		return;
	}

	int** dist;
	int** next;

	g_floyd_warshall(graph, &dist, &next);

	for (unsigned int i = 0; i < graph->vertex_count; i++) {
        if (dist[i][i] < 0) {
            printf("Graph contains a negative-weight cycle at vertex %s\n", graph->vertices[i]->room);
            return;
        }
    }

	int start_index = -1;
	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		if (graph->vertices[i] == start) {
			start_index = i;
			break;
		}
	}

	int min_dist = INF;
	Vertex* closest_exit = NULL;
	int closest_exit_index = -1;

	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		if (graph->vertices[i]->type == -1 && dist[start_index][i] < min_dist) {
			min_dist = dist[start_index][i];
			closest_exit = graph->vertices[i];
			closest_exit_index = i;
		}
	}

	if (closest_exit == NULL)
		printf("No exit was found!\n");
	else {
		printf("The closest exit is: %s\n", closest_exit->room);
		printf("The total length is: %d\n", min_dist);
		printf("Path: ");
		g_floyd_print_path(graph, next, start_index, closest_exit_index);
	}

	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		free(dist[i]);
		free(next[i]);
	}
	free(dist);
	free(next);
}


void g_floyd_warshall(Graph* graph, int*** dist_dest, int*** next_dest)
{
	int** dist = (int**)malloc(graph->vertex_count * sizeof(int*));
	int** next = (int**)malloc(graph->vertex_count * sizeof(int*));
	
	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		dist[i] = (int*)malloc(graph->vertex_count * sizeof(int));
		next[i] = (int*)malloc(graph->vertex_count * sizeof(int));
		
		for (unsigned int j = 0; j < graph->vertex_count; j++) {
			if (i == j) {
				dist[i][j] = 0;
				next[i][j] = -1;
				continue;
			}
			dist[i][j] = INF;
			next[i][j] = -1;
		}
	}

	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		Vertex* u = graph->vertices[i];
		for (unsigned int j = 0; j < u->edge_count; j++) {
			Edge* edge = u->edges[j];
			Vertex* v = edge->out;

			int v_index = -1;
			for (unsigned int k = 0; k < graph->vertex_count; k++) {
				if (graph->vertices[k] == v) {v_index = k; break;}
			}

			dist[i][v_index] = edge->length;
			next[i][v_index] = v_index;
		}
	}

	for (unsigned int k = 0; k < graph->vertex_count; k++) {
		for (unsigned int i = 0; i < graph->vertex_count; i++) {
			for (unsigned int j = 0; j < graph->vertex_count; j++) {
				if (dist[i][k] < INF && dist[k][j] < INF && dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					next[i][j] = next[i][k];
				}
			}
		}
	}
	*dist_dest = dist;
	*next_dest = next;
}


void g_floyd_print_path(Graph* graph, int** next, int start, int end)
{
	int curr = start;
	while (curr != end) {
		printf("%s -> ", graph->vertices[curr]->room);
		curr = next[curr][end];
	}
	printf("%s\n", graph->vertices[curr]->room);
}


bool g_is_empty(Graph* graph)
{
	return graph->vertex_count == 0;
}

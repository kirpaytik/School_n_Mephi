#include <stdio.h>
#include "graph.h"

void generateDot(Graph* graph, FILE* file)
{
	if (g_is_empty(graph)) {
		printf("The graph is empty!\n");
		return;
	}

	fprintf(file, "digraph BinaryGraph {\n");

	print_node_dot(graph, file);

	fprintf(file, "}\n");
}


void print_node_dot(Graph* graph, FILE* file)
{
	for (unsigned int i = 0; i < graph->vertex_count; i++) {
		Vertex* vertex = graph->vertices[i];
		fprintf(file, "\t%s [label=\"%s\\n%hd\"];\n", vertex->room, vertex->room, vertex->type);

		for (unsigned int j = 0; j < vertex->edge_count; j++) {
			Edge* edge = vertex->edges[j];

			if (edge->in == vertex) {
				fprintf(file, "\t%s -> %s [label=\"%d\"];\n", edge->in->room, edge->out->room, edge->length);
			}
		}
	}
}

#include <stdio.h>
#include "mylib.h"

int main()
{
	Graph* graph = create_graph();

	start_program(graph);

	printf("Successfully reached the end of program\n");
	endofprog(graph);

	return 0;
}
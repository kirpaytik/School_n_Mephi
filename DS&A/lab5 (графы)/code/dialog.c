#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

#define OK 0
#define BAD 1
#define END 2
#define PASS 3

#define CONSOLE_MODE 0
#define TXTFILE_MODE 1
#define BINFILE_MODE 2

#define NOFILE NULL

#define SHORT_TYPE 1
#define INT_TYPE 2
#define UINT_TYPE 3

#define EMPTYRULE_FALSE false
#define EMPTYRULE_TRUE true


short dialogue_menu(Graph* graph)
{
	short panel = 1;
	short checker, guard;
	while (panel) {
		printf("Choose an option from the list below:\n"
			"\t(1) Fill the graph with values from the file\n"
			"\t(2) Insert a vertex into the graph\n"
			"\t(3) Insert an edge into the graph\n"
			"\t(4) Delete a vertex from the graph\n"
			"\t(5) Delete an edge from the graph\n"
			"\t(6) Edit a vertex\n"
			"\t(7) Edit an edge\n"
			"\t(8) Graph traversal - check if exit is reachable from a vertex\n"
			"\t(9) Find shortest path (Bellman-Ford)\n"
			"\t(10) Find closest exit (Floyd-Warshall)\n"
			"\t(11) Print the graph\n"
			"\t(12) Finish the program\n");
		guard = read_int_inrange(&panel, SHORT_TYPE, 1, 12);
		if (guard == EOF || panel == 12) {
			printf("Finishing the program\n");
			return OK;
		}
		checker = dialog_switch(graph, panel);
		if (checker == BAD)
			return BAD;
		if (checker == END)
			return OK;
	}
	return OK;
}


short dialog_switch(Graph* graph, int panel)
{
	short checker = OK;
	switch (panel) {
	case 1:
		checker = dialog_fill_file(graph);
		break;
	case 2:
		checker = dialog_insert_vertex(graph);
		break;
	case 3:
		checker = dialog_insert_edge(graph);
		break;
	case 4:
		checker = dialog_delete_vertex(graph);
		break;
	case 5:
		checker = dialog_delete_edge(graph);
		break;
	case 6:
		checker = dialog_edit_vertex(graph);
		break;
	case 7:
		checker = dialog_edit_edge(graph);
		break;
	case 8:
		checker = dialog_traverse_bfs(graph);
		break;
	case 9:
		checker = dialog_bellmanford(graph);
		break;
	case 10:
		checker = dialog_floydwarshall(graph);
		break;
	case 11:
		checker = dialog_print(graph);
		break;
	}

	if (checker)
		return checker;
	return OK;
}


short dialog_fill_file(Graph* graph)
{
	short checker;
	FILE* file;
	checker = dialog_get_file(&file, "r\0\0");
	if (checker)
		return checker;

	short guard = EOF + 1;
	char* line;
	unsigned int num = 1;
	while (guard != EOF) {
		line = NULL;
		guard = readline(&line, file, TXTFILE_MODE, EMPTYRULE_FALSE);
		if (guard == EOF) {
			break;
		}
		checker = dialog_fill_file_line(graph, line, file);
		if (checker) {
			printf("Something wrong in file occured on line #%u\n", num + 1);
			break;
		}
		num += 2;
		free(line);
	}

	fclose(file);
	return OK;
}


short dialog_fill_file_line(Graph* graph, char* line, FILE* file)
{
	if (!line)
		return OK;
	char *room, *room2;

	int matched = sscanf(line, "%m[^ ] -> %m[^\n]", &room, &room2);
	if (matched == 2) {
		if (!job_isfound_vertex(graph, room)) {
			free(room);
			free(room2);
			return PASS;
		}

		if (!job_isfound_vertex(graph, room2)) {
			free(room);
			free(room2);
			return PASS;
		}

		int length;
		short guard = scanfTxtFileInt(&length, file);
		if (guard == EOF || !guard) {
			free(room);
			free(room2);
			return BAD;
		}

		if (job_isfound_edge(graph, room, room2))
			job_edit_edge(graph, room, room2, length);
		else
			job_insert_edge(graph, room, room2, length);

		free(room);
		free(room2);
	}
	else {
		free(room);
		matched = sscanf(line, "%m[^\n]", &room);

		int type;
		short guard = scanfTxtFileInt(&type, file);
		if (guard == EOF || !guard || type < -1 || type > 1) {
			free(room);
			return BAD;
		}

		if (job_isfound_vertex(graph, room))
			job_edit_vertex(graph, room, type);
		else
			job_insert_vertex(graph, room, type);

		free(room);
	}

	return OK;
}


short dialog_insert_vertex(Graph* graph)
{
	char* room;
	printf("room please\n");
	short guard = readline(&room, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program...\n");
		return END;
	}

	if (job_isfound_vertex(graph, room)) {
		printf("Vertex %s does already exist!\n", room);
		free(room);
		return OK;
	}

	short type;
	printf("type please\n");
	guard = read_int_inrange(&type, SHORT_TYPE, -1, 1);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program...\n");
		free(room);
		return END;
	}

	job_insert_vertex(graph, room, type);
	free(room);

	return OK;
}


short dialog_insert_edge(Graph* graph)
{
	char* room1;
	printf("room1 please\n");
	short guard = readline(&room1, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program...\n");
		return END;
	}

	if (!job_isfound_vertex(graph, room1)) {
		printf("Vertex %s does not exist!\n", room1);
		free(room1);
		return OK;
	}

	char* room2;
	printf("room2 please\n");
	guard = readline(&room2, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program...\n");
		free(room1);
		return END;
	}

	if (!job_isfound_vertex(graph, room2)) {
		printf("Vertex %s does not exist!\n", room2);
		free(room1);
		free(room2);
		return OK;
	}

	if (job_isfound_edge(graph, room1, room2)) {
		printf("Edge %s -> %s does already exist!\n", room1, room2);
		free(room1);
		free(room2);
		return OK;
	}

	int length;
	printf("length please\n");
	guard = scanfIntType(&length, NOFILE, CONSOLE_MODE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		free(room1);
		free(room2);
		return END;
	}

	job_insert_edge(graph, room1, room2, length);
	free(room1);
	free(room2);

	return OK;
}


short dialog_delete_vertex(Graph* graph)
{
	char* room;
	printf("room please\n");
	short guard = readline(&room, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program...\n");
		return END;
	}

	if (!job_isfound_vertex(graph, room)) {
		printf("Vertex %s does not exist!\n", room);
		free(room);
		return OK;
	}

	job_delete_vertex(graph, room);
	free(room);

	return OK;
}


short dialog_delete_edge(Graph* graph)
{
	char* room1;
	printf("room1 please\n");
	short guard = readline(&room1, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program...\n");
		return END;
	}

	if (!job_isfound_vertex(graph, room1)) {
		printf("Vertex %s does not exist!\n", room1);
		free(room1);
		return OK;
	}

	char* room2;
	printf("room2 please\n");
	guard = readline(&room2, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program...\n");
		free(room1);
		return END;
	}

	if (!job_isfound_vertex(graph, room2)) {
		printf("Vertex %s does not exist!\n", room2);
		free(room1);
		free(room2);
		return OK;
	}

	if (!job_isfound_edge(graph, room1, room2)) {
		printf("Edge %s -> %s does not exist!\n", room1, room2);
		free(room1);
		free(room2);
		return OK;
	}

	job_delete_edge(graph, room1, room2);
	free(room1);
	free(room2);

	return OK;
}

short dialog_edit_vertex(Graph* graph)
{
	char* room;
	printf("room please\n");
	short guard = readline(&room, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program...\n");
		return END;
	}

	if (!job_isfound_vertex(graph, room)) {
		printf("Vertex %s does not exist!\n", room);
		free(room);
		return OK;
	}

	short type_new;
	printf("new type please\n");
	guard = read_int_inrange(&type_new, SHORT_TYPE, -1, 1);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program...\n");
		free(room);
		return END;
	}

	job_edit_vertex(graph, room, type_new);
	free(room);

	return OK;
}


short dialog_edit_edge(Graph* graph)
{
	char* room1;
	printf("room1 please\n");
	short guard = readline(&room1, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program...\n");
		return END;
	}

	if (!job_isfound_vertex(graph, room1)) {
		printf("Vertex %s does not exist!\n", room1);
		free(room1);
		return OK;
	}

	char* room2;
	printf("room2 please\n");
	guard = readline(&room2, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program...\n");
		free(room1);
		return END;
	}

	if (!job_isfound_vertex(graph, room2)) {
		printf("Vertex %s does not exist!\n", room2);
		free(room1);
		free(room2);
		return OK;
	}

	if (!job_isfound_edge(graph, room1, room2)) {
		printf("Edge %s -> %s does not exist!\n", room1, room2);
		free(room1);
		free(room2);
		return OK;
	}

	int length_new;
	printf("new length please\n");
	guard = scanfIntType(&length_new, NOFILE, CONSOLE_MODE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		free(room1);
		free(room2);
		return END;
	}

	job_edit_edge(graph, room1, room2, length_new);
	free(room1);
	free(room2);

	return OK;
}


short dialog_traverse_bfs(Graph* graph)
{
	char* room;
	printf("room please\n");
	short guard = readline(&room, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program...\n");
		return END;
	}

	if (!job_isfound_vertex(graph, room)) {
		printf("Vertex %s does not exist!\n", room);
		free(room);
		return OK;
	}

	if (job_traverse_bfs(graph, room))
		printf("Yes, you can get to the exit from this vertex\n");
	else
		printf("Oops, the maze just maaayy be impossible to solve from this vertex\n");
	free(room);

	return OK;
}


short dialog_bellmanford(Graph* graph)
{
	char* room1;
	printf("room1 please\n");
	short guard = readline(&room1, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program...\n");
		return END;
	}

	if (!job_isfound_vertex(graph, room1)) {
		printf("Vertex %s does not exist!\n", room1);
		free(room1);
		return OK;
	}

	char* room2;
	printf("room2 please\n");
	guard = readline(&room2, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program...\n");
		free(room1);
		return END;
	}

	if (!job_isfound_vertex(graph, room2)) {
		printf("Vertex %s does not exist!\n", room2);
		free(room1);
		free(room2);
		return OK;
	}

	job_bellmanford(graph, room1, room2);
	free(room1);
	free(room2);

	return OK;
}


short dialog_floydwarshall(Graph* graph)
{
	char* room;
	printf("room please\n");
	short guard = readline(&room, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program...\n");
		return END;
	}

	if (!job_isfound_vertex(graph, room)) {
		printf("Vertex %s does not exist!\n", room);
		free(room);
		return OK;
	}

	job_floydwarshall(graph, room);
	free(room);

	return OK;
}


short dialog_print(Graph* graph)
{
	short guard, mode;
	printf("Where to output the graph:\n"
		"(0 - console, 1 - txt file, 2 - graphviz)\n");
	guard = read_int_inrange(&mode, SHORT_TYPE, 0, 2);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	short checker = OK;
	switch (mode) {
	case 0:
		job_print_console(graph);
		break;
	case 1:
		checker = dialog_print_txtfile(graph);
		break;
	case 2:
		checker = dialog_print_graphviz(graph);
		break;
	}

	if (checker)
		return checker;
	return OK;
}


short dialog_print_txtfile(Graph* graph)
{
	FILE* file;
	short checker = dialog_get_file(&file, "w\0\0");
	if (checker)
		return checker;

	job_print_txtfile(graph, file);
	fclose(file);

	return OK;
}


short dialog_print_graphviz(Graph* graph)
{
	short checker;
	FILE* file;
	printf("(need to add \".dot\" at the end of filename)\n");
	checker = dialog_get_file(&file, "w\0\0");
	if (checker) return checker;

	job_print_graphviz(graph, file);
	fclose(file);

	return OK;
}


short dialog_get_file(FILE** file, char filemode[3])
{
	short guard;
	char* filename;
	printf("Name of file to open:\n");
	guard = readline(&filename, NOFILE, CONSOLE_MODE, EMPTYRULE_FALSE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	*file = fopen(filename, filemode);
	free(filename);
	if (!*file) {
		printf("File opening error!\n");
		return PASS;
	}
	return OK;
}

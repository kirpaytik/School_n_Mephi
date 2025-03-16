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

#define SHORT_TYPE 1
#define INT_TYPE 2
#define UINT_TYPE 3


short dialogue_menu(Tree* tree)
{
	short panel = 1;
	short checker, guard;
	while (panel) {
		printf("Choose an option from the list below:\n"
			"\t(1) Fill the tree with values from the file\n"
			"\t(2) Insert (multiple) values into the tree\n"
			"\t(3) Insert (one) a value into the tree\n"
			"\t(4) Delete one info element from the tree\n"
			"\t(5) Delete the whole key from the tree\n"
			"\t(6) Clear the tree\n"
			"\t(7) Tree traversal (print)\n"
			"\t(8) Print the tree\n"
			"\t(9) Find elements by key\n"
			"\t(10) Special search\n"
			"\t(11) Finish the program\n");
		guard = read_int_inrange(&panel, SHORT_TYPE, 1, 11);
		if (guard == EOF || panel == 11) {
			printf("Finishing the program\n");
			return OK;
		}
		checker = dialog_switch(tree, panel);
		if (checker == BAD)
			return BAD;
		if (checker == END)
			return OK;
	}
	return OK;
}


short dialog_switch(Tree* tree, int panel)
{
	short checker = OK;
	switch (panel) {
	case 1:
		checker = dialog_fill_file(tree);
		if (checker) // может, вынести за свитч?
		// тогда по умолч ещё поставить OK, т.к. при clear ничего не будет в нём
			return checker;
		// if (!checker)
		// 	print();
		break;
	case 2:
		checker = dialog_insert_multiple(tree);
		if (checker)
			return checker;
		break;
	case 3:
		checker = dialog_insert(tree);
		if (checker)
			return checker;
		break;
	case 4:
		checker = dialog_delete(tree, 0);
		if (checker)
			return checker;
		break;
	case 5:
		checker = dialog_delete(tree, 1);
		if (checker)
			return checker;
		break;
	case 6:
		job_clear(tree);
		break;
	case 7:
		checker = dialog_traversal(tree);
		if (checker)
			return checker;
		break;
	case 8:
		checker = dialog_print(tree);
		if (checker)
			return checker;
		break;
	case 9:
		checker = dialog_find(tree, 0);
		if (checker)
			return checker;
		break;
	case 10:
		checker = dialog_find(tree, 1);
		if (checker)
			return checker;
		break;
	}
	if (checker)
		return checker;
	return OK;
}


short dialog_fill_file(Tree* tree)
{
	short checker;
	FILE* file;
	checker = dialog_get_file(&file, "r\0\0");
	if (checker)
		return checker;

	short guard = EOF + 1;
	unsigned int key;
	char* info;
	while (guard != EOF) {
		guard = scanfUIntType(&key, file, TXTFILE_MODE);
		if (guard == EOF) {
			fclose(file);
			return OK;
		}
		guard = readline(NULL, &info, file, TXTFILE_MODE);
		if (guard == EOF) {
			fclose(file);
			return OK;
		}
		if (!guard) {
			fclose(file);
			return BAD;
		}
		checker = job_insert(tree, key, info);
		if (checker) {
			fclose(file);
			free(info);
			return BAD;
		}
	}
	// fclose(file); // а сюда и не дойдёт
	return OK;
}


short dialog_insert_multiple(Tree* tree)
{
	printf("Number of values to insert:\n");
	short guard;
	unsigned int amount;
	guard = scanfUIntType(&amount, NULL, CONSOLE_MODE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	short checker;
	for (int i = 0; i < amount; i++) {
		printf("Value #%d:\n", i + 1);
		checker = dialog_insert(tree);
		if (checker) {
			return checker;
		}
	}
	return OK;
}


short dialog_insert(Tree* tree)
{
	short guard;
	unsigned int key;
	char* info;
	printf("Key to insert:\n");
	guard = scanfUIntType(&key, NULL, CONSOLE_MODE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	printf("Info to insert:\n");
	guard = readline(NULL, &info, NULL, CONSOLE_MODE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	if (!guard) {
		printf("Inputting a string error\n");
		return BAD;
	}
	short checker = job_insert(tree, key, info);
	if (checker) {
		free(info);
		return BAD;
	}
	return OK;
}


short dialog_delete(Tree* tree, short mode)
{
	short guard;
	unsigned int key;
	printf("Key to delete:\n");
	guard = scanfUIntType(&key, NULL, CONSOLE_MODE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	short checker = job_delete(tree, key, mode);
	if (checker == BAD)
		return checker;
	if (checker == -2) {
		printf("The tree is empty!\n");
		return PASS;
	}
	if (checker == -1) {
		printf("Nothing to delete was found!\n");
		return PASS;
	}
	return OK;
}


short dialog_traversal(Tree* tree)
{
	short guard, mode;
	printf("Which traversal to do:\n"
		"(0 - inOrder, -1 - preOrder, 1 - postOrder)\n");
	guard = read_int_inrange(&mode, SHORT_TYPE, -1, 1);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	int key;
	printf("Type a min key:\n"
		"(-1 if should print all keys)\n");
	guard = scanfIntType(&key, NULL, CONSOLE_MODE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	job_traversal(tree, key, mode);
	return OK;
}


short dialog_print(Tree* tree)
{
	short guard, mode;
	printf("Where to output the tree:\n"
		"(0 - console, 1 - txt file, 2 - graphviz)\n");
	guard = read_int_inrange(&mode, SHORT_TYPE, 0, 2);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	short checker;
	switch (mode) {
	case 0:
		checker = dialog_print_console(tree);
		break;
	case 1:
		checker = dialog_print_txtfile(tree);
		break;
	case 2:
		checker = dialog_print_graphviz(tree);
		break;
	}
	if (checker)
		return checker;
	return OK;
}


short dialog_print_console(Tree* tree)
{
	short guard, mode;
	// deep и breadth вроде, но предлог? типа в глубину, а у них in deep?
	printf("в глубину (громоздко) - 0 или в ширину - 1?\n");
	guard = read_int_inrange(&mode, SHORT_TYPE, 0, 1);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	// доделать: выбрать вид, ну или как там сделать, короче в консоль или graphviz
	short checker = job_print(tree, NULL, mode);
	if (checker)
		return BAD;
	return OK;
}


short dialog_print_txtfile(Tree* tree)
{
	short checker;
	FILE* file;
	checker = dialog_get_file(&file, "w\0\0");
	if (checker) {
		return checker;
	}
	checker = job_print(tree, file, 2);
	fclose(file);
	if (checker) 
		return checker;
	return OK;
}


short dialog_print_graphviz(Tree* tree)
{
	short checker;
	FILE* file;
	printf("(need to add \".dot\" at the end of filename)");
	checker = dialog_get_file(&file, "w\0\0");
	if (checker) {
		return checker;
	}
	checker = job_print(tree, file, 3);
	fclose(file);
	if (checker)
		return checker;
	return OK;
}


short dialog_find(Tree* tree, short mode)
{
	short guard;
	unsigned int key;
	printf("Key to find:\n");
	guard = scanfUIntType(&key, NULL, CONSOLE_MODE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	unsigned int foundkey, amount;
	char** infos;
	short checker = job_find(tree, key, mode, &foundkey, &amount, &infos);
	if (checker == BAD)
		return checker;
	if (checker == -2) {
		printf("The tree is empty!\n");
		return PASS;
	}
	if (checker == -1) {
		printf("The key was not found!\n");
		return PASS;
	}

	printf("The key %u was found:\n", foundkey);
	for (int i = 0; i < amount; i++) {
		printf("info #%d: %s\n", i + 1, infos[i]);
	}
	return OK;
}


short dialog_get_file(FILE** file, char filemode[3])
{
	short guard;
	char* filename;
	printf("Name of file to open:\n");
	guard = readline(NULL, &filename, NULL, CONSOLE_MODE);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	if (!guard) {
		printf("Inputting a string error\n");
		return BAD;
	}
	*file = fopen(filename, filemode);
	free(filename);
	if (!*file) {
		printf("File opening error!\n");
		return PASS;
	}
	return OK;
}

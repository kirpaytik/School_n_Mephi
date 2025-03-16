#include <stdio.h>
#include <stdlib.h>
// #include <readline/readline.h>
#include "mylib.h"

#define OK 0
#define BAD 1
#define END 2
#define PASS 3


int dialogue(Table* table, Table* table2)
{
	int panel = 1;
	int checker, guard;
	while (panel) {
		printf("Choose an option from the list below:\n\
			(1) Fill the table\n\
			(2) Insert a value into the table\n\
			(3) Delete one element from the table\n\
			(4) Clear the table\n\
			(5) Print the table\n\
			(6) Find elements by key\n\
			(7) Finish the program\n");
		guard = safeScanfInt(&panel);
		if (guard == EOF) {
			return OK;
		}
		if (panel < 0 || panel > 7) {
			printf("Number must be greater than 0 and lower than 8 !\n");
			panel = 1;
			continue;
		}
		if (panel == 7) {
			return OK;
		}
		checker = dialog_menu(table, table2, panel);
		if (checker == BAD) {
			printf("An error occured during chosen operation execution\n");
			return BAD;
		}
		if (checker == END) {
			return OK;
		}
	}
	return OK;
}


int dialog_menu(Table* table, Table* table2, int panel)
{
	int checker;
	switch (panel) {
	case 1:
		checker = dialog_fill(table);
		if (checker == BAD) {
			printf("Filling the table error\n");
			return BAD;
		}
		if (checker == END) {
			return END;
		}
		printf("Outputting: the table\n");
		job_print_console(table);
		break;
	case 2:
		checker = dialog_insert_console(table);
		if (checker == BAD) {
			printf("Inserting a value error\n");
			return BAD;
		}
		if (checker == END) {
			return END;
		}
		printf("Outputting: the table\n");
		job_print_console(table);
		break;
	case 3:
		checker = dialog_delete(table);
		if (checker == BAD) {
			printf("Deleting an element error\n");
			return BAD;
		}
		if (checker == END) {
			return END;
		}
		printf("Outputting: the table\n");
		job_print_console(table);
		break;
	case 4:
		checker = job_clear(table);
		if (checker) {
			printf("Clearing the table error\n");
			return BAD;
		}
		printf("Outputting: the table\n");
		job_print_console(table);
		break;
	case 5:
		// без звезды - так надо, потому что нет инклюда table.h
		checker = dialog_print(table, table2);
		if (checker == BAD) {
			printf("Printing the table error\n");
			return BAD;
		}
		if (checker == END) {
			return END;
		}
		break;
	case 6:
		checker = dialog_find(table, table2);
		if (checker == BAD) {
			printf("An error occured during finding the elements\n");
			return BAD;
		}
		if (checker == END) {
			return END;
		}
		break;
	}
	return OK;
}


int dialog_fill(Table* table)
{
	printf("Would you like to input data from a text file?\n");
	printf("(\"y\" if yes, '\"n\" if input from console)\n");
	char panel = '\0';
	int guard = read_y_or_n(&panel);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	int checker;
	if (panel == 'y') {
		checker = dialog_fill_file(table);
	}
	else {
		checker = dialog_fill_console(table);
	}
	if (checker == BAD) {
		printf("Fillng the table error\n");
		return BAD;
	}
	if (checker == END) {
		return END;
	}
	return OK;
}


int dialog_fill_console(Table* table)
{
	printf("Input a number of values to fill:\n");
	int amount;
	int guard = safeScanfInt(&amount);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	int i;
	int checker;
	printf("Enter %d values to fill:\n", amount);
	for (i = 0; i < amount; i++) {
		printf("Value to fill #%d:\n", i + 1);
		checker = dialog_insert_console(table);
		if (checker == BAD) {
			printf("Inserting a value error\n");
			return BAD;
		}
		if (checker == END) {
			return END;
		}
	}
	return OK;
}


int dialog_insert_console(Table* table) 
{
	unsigned int key;
	int guard;
	printf("Enter a key:\n");
	guard = safeScanfUInt(&key);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	char* info;
	printf("Enter an info:\n>>> ");
	info = readline("");
	if (!info) {
		printf("Inputting a string error\n");
		printf("(info to insert)\n");
		return BAD;
	}
	if (*info == '\0') {
		printf("Ctrl+D detected. Ending the program\n");
		free(info);
		return END;
	}
	printf("Inserting the value...\n");
	int checker = job_insert(table, key, info);
	if (checker) {
		printf("job error\n");
		return BAD;
	}
	return OK;
}


int dialog_fill_file(Table* table) {
	char* filename;
	printf("Enter a file name:\n>>> ");
	filename = readline("");
	if (!filename || *filename == '\0') {
		printf("Inputting a string error\n");
		printf("(name of file to open)\n");
		free(filename);
		return BAD;
	}
	FILE* file = fopen(filename, "r");
	free(filename);
	if (!file) {
		printf("File opening error!\n");
		// return OK, потому что это не ломает прогу, и можно продолжать
		// ну а вдруг он опечатался в имени файла просто
		return OK;
	}
	int amount;
	int guard = safeFileScanfInt(&amount, file);
	if (guard < 1) {
		printf("Inputting an integer value error\n");
		printf("(amount of values to fill)\n");
		return OK;
	}
	int i;
	int checker;
	for (i = 0; i < amount; i++) {
		checker = dialog_insert_file(table, file);
		if (checker == BAD) {
			printf("Inserting a value error\n");
			fclose(file);
			return BAD;
		}
		if (checker == END) {
			fclose(file);
			return END;
		}
		if (checker == PASS) {
			fclose(file);
			printf("(value to fill #%d)\n", i + 1);
			return OK;
		}
	}
	fclose(file);
	return OK;
}


int dialog_insert_file(Table* table, FILE* file) 
{
	unsigned int key;
	int guard;
	guard = safeFileScanfUInt(&key, file);
	if (guard < 1) {
		printf("Inputting an integer value error\n");
		printf("(unsigned int key)\n");
		return PASS;
	}
	char* info;
	info = readFileLine("", file);
	if (!info) {
		printf("Inputting a string error\n");
		printf("(info to insert)\n");
		return PASS;
	}
	int checker = job_insert(table, key, info);
	if (checker) {
		printf("job error\n");
		return BAD;
	}
	return OK;
}


int dialog_delete(Table* table) 
{
	unsigned int key;
	int guard;
	printf("Enter a key:\n");
	guard = safeScanfUInt(&key);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	int rel;
	printf("Would you like to delete all \"%d\" keys or just one release?\n", key);
	printf("(type 0 if all or type the release)\n");
	guard = safeScanfInt(&rel);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	printf("Deleting the value...\n");
	int checker = job_delete(table, key, rel);
	if (checker) {
		printf("job error\n");
		return BAD;
	}
	return OK;
}


int dialog_find(Table* table, Table* table2)
{
	int checker;
	unsigned int key;
	int rel;
	printf("Enter a key:\n");
	int guard = safeScanfUInt(&key);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	printf("Enter a release to find:\n");
	printf("(type 0 if all or type the release)\n");
	guard = safeScanfInt(&rel);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return OK;
	}
	printf("Finding the values...\n");
	checker = job_find(table, key, rel, table2);
	if (checker == 2) {
		printf("Nothing found!\n");
		return OK;
	}
	else if (checker) {
		printf("job error\n");
		return BAD;
	}
	return OK;
}


int dialog_print(Table* table, Table* table2)
{
	printf("What table do you want to print?\n");
	printf("(1 if main table, 2 if find-table)\n");
	int num = 0, guard;
	while (num < 1 || num > 2) {
		guard = safeScanfInt(&num);
		if (guard == EOF) {
			printf("Ctrl+D detected. Ending the program\n");
			return END;
		}
		if (num < 1 || num > 2) {
			printf("Type '1' or '2'!\n");
		}
	}
	printf("Would you like to output data in a text file?\n");
	printf("(\"y\" if yes, \"n\" if output in console)\n");
	char panel = '\0';
	guard = read_y_or_n(&panel);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	if (panel == 'n') {
		printf("Outputting: the table\n");
		if (num == 1) {
			job_print_console(table);
		}
		else {
			job_print_console(table2);
		}
		return OK;
	}
	char* filename;
	printf("Enter a file name:\n>>> ");
	filename = readline("");
	if (!filename || *filename == '\0') {
		printf("Inputting a string error\n");
		printf("(name of file to open)\n");
		free(filename);
		return BAD;
	}
	FILE* file = fopen(filename, "w");
	free(filename);
	if (!file) {
		printf("File opening error!\n");
		return OK;
	}
	if (num == 1) {
		job_print_file(table, file);
	}
	else {
		job_print_file(table2, file);
	}
	fclose(file);
	return OK;
}

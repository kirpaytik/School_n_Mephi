#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

#define OK 0
#define BAD 1
#define END 2
#define PASS 3


int dialogue_start(Table* table)
{
	int msize, guard;
	printf("Input table's size (it will be rounded up to a prime number)\n");
	guard = scanfInt(&msize, NULL, 0);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	while (msize < 1) {
		printf("Give the table at least 1 element pls:(\n");
		guard = scanfInt(&msize, NULL, 0);
		if (guard == EOF) {
			printf("Ctrl+D detected. Ending the program\n");
			return END;
		}
	}
	int checker = job_set_size(table, msize, 1);
	if (checker) {
		printf("job error\n");
		printf("(setting table's size)\n");
		return BAD;
	}
	checker = dialog_menu(table);
	return checker;
}


int dialog_menu(Table* table)
{
	int panel = 1;
	int checker, guard;
	while (panel) {
		printf("Choose an option from the list below:\n\
			(1) Fill the table with values (will be resized if necessary)\n\
			(2) Insert a value into the table\n\
			(3) Delete one element from the table\n\
			(4) Clear the table\n\
			(5) Print the table\n\
			(6) Find elements by key\n\
			(7) Finish the program\n");
		guard = read_int_inrange(&panel, 1, 7);
		if (guard == EOF || panel == 7) {
			printf("Finishing the program\n");
			return OK;
		}
		checker = dialog_switch(table, panel);
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


int dialog_switch(Table* table, int panel)
{
	int checker;
	switch (panel) {
	case 1:
		checker = dialog_fill(table);
		if (checker) {
			if (checker == BAD) {
				printf("Filling the table error\n");
			}
			return checker;
		}
		printf("Outputting the table:\n");
		job_print(table, NULL, 0);
		break;
	case 2:
		checker = dialog_insert_console(table);
		if (checker) {
			if (checker == BAD) {
				printf("Inserting a value error\n");
			}
			return checker;
		}
		printf("Outputting the table:\n");
		job_print(table, NULL, 0);
		break;
	case 3:
		checker = dialog_delete(table);
		if (checker) {
			if (checker == BAD) {
				printf("Deleting an element error\n");
			}
			return checker;
		}
		printf("Outputting the table:\n");
		job_print(table, NULL, 0);
		break;
	case 4:
		checker = job_clear(table);
		if (checker == BAD) {
			printf("Clearing the table error\n");
			return BAD;
		}
		if (checker == PASS) {
			printf("Nothing to delete was found!\n");
			return OK;
		}
		printf("Outputting the table:\n");
		job_print(table, NULL, 0);
		break;
	case 5:
		// без звезды - так надо, потому что нет инклюда table.h
		checker = dialog_print(table);
		if (checker) {
			if (checker == BAD) {
				printf("Printing the table error\n");
			}
			return checker;
		}
		break;
	case 6:
		checker = dialog_find(table);
		if (checker) {
			if (checker == BAD) {
				printf("An error occured during finding the elements\n");
			}
			return checker;
		}
		break;
	}
	return OK;
}


int dialog_fill(Table* table)
{
	printf("Where would you like to input data from?\n");
	printf("0 is for console, 1 is for text file, 2 is for binary file\n");
	int panel;
	int guard = read_int_inrange(&panel, 0, 2);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	int checker;
	if (panel == 0) {
		checker = dialog_fill_console(table);
	}
	else {
		char* filename;
		printf("Enter a file name:\n");
		guard = readline("", &filename);
		if (guard == EOF) {
			printf("Ctrl+D detected. Ending the program\n");
			return END;
		}
		if (!guard) {
			printf("Inputting a string error\n");
			printf("(name of file to open)\n");
			return BAD;
		}
		char filemode[3] = "r\0\0";
		if (panel == 2) {
			filemode[1] = 'b';
		}
		FILE* file = fopen(filename, filemode);
		free(filename);
		if (!file) {
			printf("File opening error!\n");
			return PASS;
		}
		checker = dialog_fill_file(table, file, panel);
	}
	if (checker) {
		if (checker == BAD) {
			printf("Fillng the table error\n");
		}
		return checker;
	}
	return OK;
}


int dialog_fill_console(Table* table)
{
	printf("Input a number of values to fill:\n");
	int amount;
	int guard = scanfInt(&amount, NULL, 0); // whoops! Забыл проверить amount на <0, и из-за job_set_size, думаю, будет плохо))
// спойлер: не будет, на job вернётся сюда, не дойдя до table.c, но это повезло
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	int checker = job_set_size(table, amount, 0);
	if (checker) {
		printf("Table resizing error\n");
		return checker;
	}
	int i;
	printf("Enter %d values to fill:\n", amount);
	for (i = 0; i < amount; i++) {
		printf("Value to fill #%d:\n", i + 1);
		checker = dialog_insert_console(table);
		if (checker) {
			if (checker == BAD) {
				printf("Inserting a value error\n");
			}
			return checker;
		}
	}
	return OK;
}


int dialog_insert_console(Table* table) 
{
	unsigned int key;
	int guard;
	printf("Enter a key:\n");
	guard = scanfUInt(&key, NULL, 0);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	printf("Enter an info:\n");
	unsigned int info;
	guard = scanfUInt(&info, NULL, 0);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	printf("Inserting the value...\n");
	int checker = job_insert(table, key, info);
	if (checker == BAD) {
		printf("job error\n");
		return BAD;
	}
	if (checker == -1) {
		printf("The same key already exists!\n");
		return PASS;
	}
	if (checker == -2) {
		printf("The table is full and couldnt expand it!\n");
		return PASS;
	}
	return OK;
}


int dialog_fill_file(Table* table, FILE* file, int mode) {
	int amount;
	int guard = scanfInt(&amount, file, mode);
	if (guard < 1) {
		printf("Inputting an integer value error\n");
		if (guard == EOF) {
			printf("(EOF)\n");
		}
		printf("(amount of values to fill)\n");
		return PASS;
	}
	int checker = job_set_size(table, amount, 0); // whoops! Забыл проверить amount на <0, и тут будет плохо))
// спойлер: не будет, на job вернётся сюда, не дойдя до table.c, но это повезло
	if (checker) {
		printf("Table resizing error\n");
		return checker;
	}
	int i;
	for (i = 0; i < amount; i++) {
		checker = dialog_insert_file(table, file, mode);
		if (checker) {
			if (checker == BAD) {
				printf("Inserting a value error\n");
			}
			printf("(value to fill #%d)\n", i + 1);
			fclose(file);
			return checker;
		}
	}
	fclose(file);
	return OK;
}


int dialog_insert_file(Table* table, FILE* file, int mode) 
{
	unsigned int key;
	int guard;
	guard = scanfUInt(&key, file, mode);
	if (guard < 1) {
		printf("Inputting an integer value error\n");
		if (guard == EOF) {
			printf("(EOF)\n");
		}
		printf("(unsigned int key)\n");
		return PASS;
	}
	unsigned int info;
	guard = scanfUInt(&info, file, mode);
	if (guard < 1) {
		printf("Inputting an integer value error\n");
		if (guard == EOF) {
			printf("(EOF)\n");
		}
		printf("(unsigned int info)\n");
		return PASS;
	}
	int checker = job_insert(table, key, info);
	if (checker == BAD) {
		printf("job error\n");
		return BAD;
	}
	if (checker == -1) {
		printf("The same key already exists!\n");
		printf("(key = %u)\n", key);
		return OK;
	}
	if (checker == -2) {
		printf("The table is full and couldnt expand it!\n");
		return PASS;
	}
	return OK;
}


int dialog_delete(Table* table) 
{
	unsigned int key;
	int guard;
	printf("Enter a key:\n");
	guard = scanfUInt(&key, NULL, 0);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	printf("Deleting the value...\n");
	int checker = job_delete(table, key);
	if (checker == BAD) {
		printf("job error\n");
		return BAD;
	}
	if (checker == PASS) {
		printf("Nothing to delete was found!\n");
	}
	return OK;
}


int dialog_find(Table* table)
{
	int checker;
	unsigned int key;
	printf("Enter a key:\n");
	int guard = scanfUInt(&key, NULL, 0);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	printf("Finding the values...\n");
	KeySpace ks = (KeySpace){0,0,0};
	checker = job_find(table, key, &ks);
	if (checker == -1) {
		printf("Nothing found!\n");
		return OK;
	}
	if (checker) {
		printf("job error\n");
		return BAD;
	}
	printf("Found the value (key, busy, info):\n");
	printf("%u %d %u\n", key, ks.busy, ks.info);
	return OK;
}


int dialog_print(Table* table)
{
	printf("Where would you like to output data?\n");
	printf("0 is for console, 1 is for text file, 2 is for binary file\n");
	int panel;
	int guard = read_int_inrange(&panel, 0, 2);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	if (panel == 0) {
		printf("Outputting the table\n");
		job_print(table, NULL, 0);
		return OK;
	}
	char* filename;
	printf("Enter a file name:\n");
	guard = readline("", &filename);
	if (guard == EOF) {
		printf("Ctrl+D detected. Ending the program\n");
		return END;
	}
	if (!guard) {
		printf("Inputting a string error\n");
		printf("(name of file to open)\n");
		return BAD;
	}
	char filemode[3] = "w\0\0";
	if (panel == 2) {
		filemode[1] = 'b';
	}
	FILE* file = fopen(filename, filemode);
	free(filename);
	if (!file) {
		printf("File opening error!\n");
		return OK;
	}
	job_print(table, file, panel);
	fclose(file);
	return OK;
}

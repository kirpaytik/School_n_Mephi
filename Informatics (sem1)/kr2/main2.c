#include "funny.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main()
{
	char* string = readline("---> ");
	char* new = process2(string);
	printf("old is: %s\n", string);
	printf("New is: %s\n", new);
	free(new);
	free(string);
	return 0;
}
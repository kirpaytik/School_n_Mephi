#include <stdio.h>
#ifdef USE_MYLIB
#include "mylib.h"
#else
#include "dop.h"
#endif

int main()
{
	Tree* tree;
	short checker = create_tree(&tree);
	if (checker) {
		printf("Tree creating error\n");
		endofprog(NULL);
		return 1;
	}

	checker = start_program(tree);
	if (checker) {
		endofprog(tree);
		return 1;
	}

	printf("Successfully reached the end of program\n");
	endofprog(tree);
	return 0;
}
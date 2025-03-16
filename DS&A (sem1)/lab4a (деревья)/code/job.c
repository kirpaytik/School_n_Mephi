#include <stdlib.h>
#include "mylib.h"
#include "tree.h"

#define OK 0
#define BAD 1
#define PASS 3


short create_tree(Tree** dest)
{
	return t_create(dest);
}


void endofprog(Tree* tree)
{
	t_free(tree);
	free(tree);
}


short start_program(Tree* tree)
{
	short checker = dialogue_menu(tree);
	return checker;
}


short job_insert(Tree* tree, unsigned int key, char* info)
{
	KeySpace ks = (KeySpace){key, info};
	return t_insert(tree, ks);
}


short job_delete(Tree* tree, unsigned int key, short mode)
{
	short checker = t_delete(tree, key);
	if (checker)
		return checker;
	if (mode == 0)
		return OK;

	while (!checker) {
		checker = t_delete(tree, key);
	}
	if (checker == BAD)
		return checker;
	return OK;
}


void job_clear(Tree* tree)
{
	t_free(tree);
}


void job_traversal(Tree* tree, unsigned int key, short mode)
{
	switch (mode) {
	case -1:
		t_preOrder_traversal(tree, key);
		break;
	case 0:
		t_inOrder_traversal(tree, key);
		break;
	case 1:
		t_postOrder_traversal(tree, key);
		break;
	}
}


short job_print(Tree* tree, FILE* file, short mode)
{
	switch (mode) {
	case 0:
		t_print_console_type1(tree);
		return OK;
	case 1:
		return t_print_console_type2(tree);
	case 2:
		t_print_txtfile(tree, file);
		return OK;
	case 3:
		generateDot(tree, file);
		return OK;
	}
}


short job_find(Tree* tree, unsigned int key, short mode,
    unsigned int* foundkey, unsigned int* amount, char*** dest)
{
	short checker;
	Node* ptr;
	if (mode == 0) {
		checker = t_find(tree, key, &ptr);
	}
	else {
		checker = t_special_search(tree, key, &ptr);
	}
	if (checker)
		return checker;

	*foundkey = ptr->key;
	*amount = ptr->amount;
	*dest = ptr->infos;
	return OK;
}

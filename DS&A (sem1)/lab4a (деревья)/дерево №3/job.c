#include <stdlib.h>
#include "mylib.h"
#include "tree.h"

#define OK 0
#define MEMORY 4
#define TREE_DUPLICATE -1


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


short job_insert(Tree* tree, char* key, unsigned int info, unsigned int* previnfo)
{
	KeySpace ks = (KeySpace){key, info};
	unsigned int foundinfo;
	short checker = t_insert(tree, ks, &foundinfo);
	if (checker == TREE_DUPLICATE && previnfo)
		*previnfo = foundinfo;
	return checker;
}


short job_delete(Tree* tree, char* key)
{
	return t_delete(tree, key);
}


void job_clear(Tree* tree)
{
	t_free(tree);
}


void job_traversal(Tree* tree, char* key, short mode)
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
	}
}


short job_find(Tree* tree, char* key, short mode,
    char** foundkey, unsigned int* foundinfo)
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
	*foundinfo = ptr->info;
	return OK;
}

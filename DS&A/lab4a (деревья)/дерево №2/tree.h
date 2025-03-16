#ifndef TREE_H
#define TREE_H

// структура KeySpace и просто typedef Tree там
#include "mylib.h"

typedef struct Node {
	char* key;
	struct Node* parent;
	struct Node* left;
	struct Node* right;
	unsigned int* infos;
	unsigned int amount;
	short printed;
} Node;


// struct Tree
short t_create(Tree** dest);
// short t_set_size(Tree* tree, int msize);
void t_free(Tree* tree);
void t_free_node(Node* node);
void t_print_console_type1(Tree* tree);
short t_print_console_type2(Tree* tree); // не void, т.к. используется queue
void t_print_txtfile(Tree* tree, FILE* file);

short t_insert(Tree* tree, KeySpace ks);
short t_delete(Tree* tree, char* key);
short t_find_next(Tree* tree, Node* ptr, Node** dest);
void t_inOrder_traversal(Tree* tree, char* key);
void t_preOrder_traversal(Tree* tree, char* key);
void t_postOrder_traversal(Tree* tree, char* key);
short t_find(Tree* tree, char* key, Node** dest);
short t_special_search(Tree* tree, char* key, Node** dest);

short t_is_empty(Tree* tree);
unsigned int t_get_maxheight(Tree* tree);
unsigned int get_subtree_amount(unsigned int height, unsigned int maxheight);

#endif

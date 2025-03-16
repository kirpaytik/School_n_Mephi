#ifndef TREE_H
#define TREE_H

// структура KeySpace и просто typedef Tree там
#ifdef USE_MYLIB
#include "mylib.h"
#else
#include "dop.h"
#endif

typedef struct Node {
	unsigned int key;
	struct Node* parent;
	struct Node* left;
	struct Node* right;
	char** infos;
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
short t_delete(Tree* tree, unsigned int key);
short t_find_next(Tree* tree, Node* ptr, Node** dest);
void t_inOrder_traversal(Tree* tree, unsigned int key);
void t_preOrder_traversal(Tree* tree, unsigned int key);
void t_postOrder_traversal(Tree* tree, unsigned int key);
short t_find(Tree* tree, unsigned int key, Node** dest);
short t_special_search(Tree* tree, unsigned int key, Node** dest);

short t_is_empty(Tree* tree);
int t_get_height(Tree* tree);
int get_subtree_amount(int height, int maxheight);

// visual.c - for graphviz
void generateDot(Tree* tree, FILE* file);
void print_node_dot(Tree* tree, FILE* file, unsigned int* counter);

// dop
void t_count(Tree* tree);

#endif

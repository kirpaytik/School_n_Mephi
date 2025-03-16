#ifndef TREE_H
#define TREE_H

// структура KeySpace и просто typedef Tree там
#include "mylib.h"

typedef struct Node {
        char* key;
        unsigned int info;
        struct Node* parent;
        struct Node* left;
        struct Node* right;
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

short t_insert(Tree* tree, KeySpace ks, unsigned int* previnfo);
short t_insert_common(Tree* tree, KeySpace ks, Node** new, unsigned int* height, unsigned int* previnfo);
Node* t_find_theGOAT(Node* last, double alpha);
short t_is_balanced(Node* hostage, double alpha);
unsigned int t_getSize(Node* node);
short t_rebuildTree(Tree* tree, Node* goat);
short t_rebuild_traversal(Node* goat, Node*** dest, unsigned int size_dest);
Node* t_buildSubtree(int start, int end, Node** goatTree);
short t_delete(Tree* tree, char* key);
short t_delete_common(Tree* tree, char* key);
short t_find_next(Node* ptr, Node** dest);
void t_inOrder_traversal(Tree* tree, char* key);
void t_preOrder_traversal(Tree* tree, char* key);
void t_postOrder_traversal(Tree* tree, char* key);
short t_find(Tree* tree, char* key, Node** dest, unsigned int* height);
short t_special_search(Tree* tree, char* key, Node** dest);

short t_is_empty(Tree* tree);
unsigned int t_get_maxheight(Tree* tree);
unsigned int get_subtree_amount(unsigned int height, unsigned int maxheight);

double logarithm(double num, double base);

// visual.c - for graphviz
void generateDot(Tree* tree, FILE* file);
void print_node_dot(Tree* tree, FILE* file, unsigned int* counter);

#endif
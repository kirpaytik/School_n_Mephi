#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
	struct Node* up_left;
	struct Node* up_right;
	struct Node* down_left;
	struct Node* down_right;
	struct Node* parent;
	int color;
} Node;

typedef struct CaTree {
	Node* root;
	int amount;
} CaTree;


CaTree* t_create(int amount);
Node* node_create();
void t_free(CaTree* tree);
void t_insert(CaTree* tree, int index, int color);
double log4(double x);


CaTree* t_create(int amount)
{
	CaTree* tree = (CaTree*)malloc(sizeof(CaTree));

	tree->root = NULL;
	tree->amount = amount;

	return tree;
}


Node* node_create()
{
	Node* new = (Node*)malloc(sizeof(Node));

	new->up_left = NULL;
	new->up_right = NULL;
	new->down_left = NULL;
	new->down_right = NULL;
	new->parent = NULL;
	new->color = 0;

	return new;
}


void t_free(CaTree* tree)
{
	Node* ptr = tree->root;
	Node* temp;

	while (ptr) {
		if (ptr->up_left) {
			ptr = ptr->up_left;
			ptr->parent->up_left = NULL;
			continue;
		}

		if (ptr->up_right) {
			ptr = ptr->up_right;
			ptr->parent->up_right = NULL;
			continue;
		}

		if (ptr->down_left) {
			ptr = ptr->down_left;
			ptr->parent->down_left = NULL;
			continue;
		}

		if (ptr->down_right) {
			ptr = ptr->down_right;
			ptr->parent->down_right = NULL;
			continue;
		}

		temp = ptr->parent;
		free(ptr);
		ptr = temp;
	}
}


void t_insert(CaTree* tree, int index, int color)
{
	if (!tree->root) {
		tree->root = node_create();
	}

	Node* ptr = tree->root;
	int coef = tree->amount;

	for (int i = 0; i < log4(tree->amount); i++) {
		coef /= 4;
		int side = index / coef;
		index %= coef;

		if (side == 0) {
			if (!ptr->up_left) {
				ptr->up_left = node_create();
			}
			ptr->up_left->parent = ptr;
			ptr = ptr->up_left;
		}

		if (side == 1) {
			if (!ptr->up_right) {
				ptr->up_right = node_create();
			}
			ptr->up_right->parent = ptr;
			ptr = ptr->up_right;
		}

		if (side == 2) {
			if (!ptr->down_left) {
				ptr->down_left = node_create();
			}
			ptr->down_left->parent = ptr;
			ptr = ptr->down_left;
		}

		if (side == 3) {
			if (!ptr->down_right) {
				ptr->down_right = node_create();
			}
			ptr->down_right->parent = ptr;
			ptr = ptr->down_right;
		}
	}

	ptr->color = color;

	ptr = ptr->parent;
	while (ptr) {
		if (!ptr->up_left || !ptr->up_right || !ptr->down_right || !ptr->down_left)
			break;

		if (ptr->up_left->color && ptr->up_right->color && ptr->down_right->color && ptr->down_left->color) {
			ptr->color = 1;
			ptr->up_left = NULL;
			ptr->up_right = NULL;
			ptr->down_left = NULL;
			ptr->down_right = NULL;
			free(ptr->up_left);
			free(ptr->up_right);
			free(ptr->down_left);
			free(ptr->down_right);
			continue;
		}
		break;
	}
}


double log4(double x)
{
	return log(x) / log(4);
}


int main()
{
	int amount = 64;
	int data[16][16] = {{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,1,1,1,0},
						{0,0,0,0,1,1,0,0},
						{1,1,1,1,1,1,0,0},
						{1,1,1,1,1,1,0,0},
						{1,1,1,1,0,0,0,0},
						{1,1,1,1,0,0,0,1}};

	CaTree* tree = t_create(amount);

	for (int i = 0; i < amount; i++) {
		t_insert(tree, i, data[i % 4][i / 4]);
	}

	t_free(tree);
	free(tree);

	return 0;
}

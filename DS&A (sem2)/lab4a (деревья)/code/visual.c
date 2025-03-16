#include <stdio.h>
#include "tree.h"

struct Tree {
	Node* root;
};

void generateDot(Tree* tree, FILE* file)
{
	if (t_is_empty(tree)) {
		printf("The tree is empty!\n");
		return;
	}
	fprintf(file, "digraph BinaryTree {\n");
	fprintf(file, "\tedge [dir=forward]\n");
	fprintf(file, "\trankdir=TB\n\n");

	unsigned int count, i;
	print_node_dot(tree, file, &count);
	fprintf(file, "\n");
	for (i = 0; i < count; i++)
		fprintf(file, "\tinv%u [style=invis];\n", i);

	fprintf(file, "}\n");
}


void print_node_dot(Tree* tree, FILE* file, unsigned int* counter)
{
	Node* ptr = tree->root;
	unsigned int count = 0;
	while (ptr) {
		if (!ptr->left && !ptr->right) {
			ptr = ptr->parent;
			continue;
		}
		if (ptr->left && !(ptr->printed & 2)) {
			fprintf(file, "\t%u -> %d;\n", ptr->key, ptr->left->key);
			ptr->printed |= 2;
			ptr = ptr->left;
			continue;
		}
		if (!(ptr->printed & 1)) {
			fprintf(file, "\t%u -> inv%u [style=invis];\n", ptr->key, count);
			count++;
			if (!ptr->left || !ptr->right) {
				fprintf(file, "\t%u -> inv%u [style=invis];\n", ptr->key, count);
				count++;
			}
		}
		if (ptr->right && !(ptr->printed & 1)) {
			fprintf(file, "\t%u -> %u;\n", ptr->key, ptr->right->key);
			ptr->printed |= 1;
			ptr = ptr->right;
			continue;
		}
		ptr->printed = 0;
		ptr = ptr->parent;
	}
	*counter = count;
}

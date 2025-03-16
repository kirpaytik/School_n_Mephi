#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "tree.h"
#include "queue.h"

#define OK 0
#define BAD 1

struct Tree {
	Node* root;
};


short t_create(Tree** dest)
{
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	if (tree == NULL) {
		printf("Memory allocation error\n");
		return BAD;
	}
	tree->root = NULL;
	*dest = tree;
	return OK;
}


void t_free(Tree* tree)
{
	if (!tree)
		return;

	Node* ptr = tree->root;
	Node* temp;
	while (ptr) {
		if (ptr->left) {
			ptr = ptr->left;
			continue;
		}
		if (ptr->right) {
			ptr = ptr->right;
			continue;
		}
		temp = ptr;
		ptr = ptr->parent;
		t_free_node(temp);
		free(temp);
		if (!ptr) {
			break;
		}
		if (ptr->left) {
			ptr->left = NULL;
			continue;
		}
		ptr->right = NULL;
	}
	tree->root = NULL;
}


void t_free_node(Node* node)
{
	int i;
	for (i = 0; i < node->amount; i++) {
		free(node->infos[i]);
		node->infos[i] = NULL;
	}
	free(node->infos);
	node->infos = NULL;
}


void t_print_console_type1(Tree* tree)
{
	if (t_is_empty(tree)) {
		printf("The tree is empty\n");
		return;
	}
	int h = 0, maxh = t_get_height(tree);
	Node* ptr = tree->root;
	while (ptr) {
		if (!ptr->right && !(ptr->printed & 1)) {
			for(int i = 0; i < get_subtree_amount(h, maxh) / 2; i++)
				printf("\n");
			ptr->printed |= 1;
		}
		if (ptr->right && !(ptr->printed & 1)) {
			ptr->printed |= 1;
			ptr = ptr->right;
			h++;
			continue;
		}
		if (!(ptr->printed & 4)) {
			for (int i = 0; i < h; i++) {
				printf("\t");
			}
			printf("%u\n", ptr->key);
			ptr->printed |= 4;
		}
		if (!ptr->left && !(ptr->printed & 2)) {
			for(int i = 0; i < get_subtree_amount(h, maxh) / 2; i++)
				printf("\n");
			ptr->printed |= 2;
		}
		if (ptr->left && !(ptr->printed & 2)) {
			ptr->printed |= 2;
			ptr = ptr->left;
			h++;
			continue;
		}
		ptr->printed = 0;
		ptr = ptr->parent;
		h--;
	}
}


short t_print_console_type2(Tree* tree)
{
	if (t_is_empty(tree)) {
		printf("The tree is empty\n");
		return OK;
	}
	Queue* que;
	short checker = q_create(&que);
	if (checker)
		return BAD;
	checker = q_insert(que, tree->root, 0, "");
	if (checker) {
		free(que);
		return BAD;
	}
	int currLevel = 0;
	QueueNode quenode;
	unsigned int i;

	while (!q_is_empty(que)) {
		checker = q_delete(que, &quenode);
		if (checker)
			break;
		Node* treeNode = quenode.treeNode;
        int level = quenode.level;
        char* prefix = quenode.prefix;

        if (level > currLevel) {
            printf("%d\n", level);
            currLevel = level;
        }
        printf("%s┌──%u\n", prefix, treeNode->key);
        for (i = 0; i < treeNode->amount - 1; i++) {
        	printf("%s, ", treeNode->infos[i]);
        }
        printf("%s\n", treeNode->infos[i]);

        char newPrefix[1024];
        if (treeNode->left) {
        	snprintf(newPrefix, sizeof(newPrefix), "%s.\t", prefix);
            checker = q_insert(que, treeNode->left, level + 1, newPrefix);
            if (checker) {
	        	free(prefix);
	        	q_free(que);
	        	free(que);
            	return BAD;
            }
        }
        if (treeNode->right) {
            snprintf(newPrefix, sizeof(newPrefix), "%s|\t", prefix);
            checker = q_insert(que, treeNode->right, level + 1, newPrefix);
            if (checker) {
	        	free(prefix);
	        	q_free(que);
	        	free(que);
            	return BAD;
            }
        }

        free(prefix);
	}
	printf("\n");
	q_free(que);
	free(que);
	return OK;
}


void t_print_txtfile(Tree* tree, FILE* file)
{
	Node* ptr = tree->root;
	while (ptr) {
		if (!(ptr->printed & 4)) {
			for (int i = 0; i < ptr->amount; i++)
				fprintf(file, "%u\n%s\n", ptr->key, ptr->infos[i]);
			ptr->printed |= 4;
		}
		if (ptr->left && !(ptr->printed & 2)) {
			ptr->printed |= 2;
			ptr = ptr->left;
			continue;
		}
		if (ptr->right && !(ptr->printed & 1)) {
			ptr->printed |= 1;
			ptr = ptr->right;
			continue;
		}
		ptr->printed = 0;
		ptr = ptr->parent;
	}
}


short t_insert(Tree* tree, KeySpace ks)
{
	Node new = (Node){ks.key, NULL, NULL, NULL, NULL, 0, 0};
	if (!tree->root) {
		Node* node = (Node*)malloc(sizeof(Node));
		if (!node) {
			printf("Memory allocation error\n");
			return BAD;
		}
		*node = new;
		node->infos = (char**)malloc(sizeof(char*));
		if (!node->infos) {
			printf("Memory allocation error\n");
			return BAD;
		}
		node->infos[0] = ks.info;
		node->amount = 1;
		tree->root = node;
		return OK;
	}

	Node* ptr;
	short checker = t_find(tree, ks.key, &ptr);

	if (checker == OK) {
		char** temp = (char**)realloc(ptr->infos, (ptr->amount + 1) * sizeof(char*));
		if (!temp) {
			printf("Memory allocation error\n");
			return BAD;
		}
		ptr->infos = temp;
		ptr->infos[ptr->amount] = ks.info;
		ptr->amount++;
		return OK;
	}

	Node* node = (Node*)malloc(sizeof(Node));
	if (!node) {
		printf("Memory allocation error\n");
		return BAD;
	}
	*node = new;
	node->infos = (char**)malloc(sizeof(char*));
	if (!node->infos) {
		printf("Memory allocation error\n");
		return BAD;
	}
	node->infos[0] = ks.info;
	node->amount = 1;

	node->parent = ptr;
	if (ks.key < ptr->key)
		ptr->left = node;
	else
		ptr->right = node;

	return OK;
}


short t_delete(Tree* tree, unsigned int key)
{
	Node* ptr;
	short checker = t_find(tree, key, &ptr);
	if (checker) {
		return checker;
	}
	if (ptr->amount > 1) {
		free(ptr->infos[0]);
		for (int i = 0; i < ptr->amount - 1; i++) {
			ptr->infos[i] = ptr->infos[i + 1];
		}
		char** temp = (char**)realloc(ptr->infos, (ptr->amount - 1) * sizeof(char*));
		if (!temp) {
			printf("Memory allocation error\n");
			return BAD;
		}
		ptr->infos = temp;
		ptr->amount--;
		return OK;
	}

	Node *real = ptr;
	if (ptr->left && ptr->right)
		checker = t_find_next(tree, ptr, &real);
	// гарантируется (нетрудно понять), что у real не более 1 поддерева
	Node* next = real->left;
	if (!real->left)
		next = real->right;

	Node* parent = real->parent;
	if (next)
		next->parent = parent;
	if (!parent) {
		t_free_node(real);
		free(real);
		tree->root = next;
		return OK;
	}
	if (parent->left == real)
		parent->left = next;
	else
		parent->right = next;

	if (ptr != real) {
		t_free_node(ptr);
		ptr->key = real->key;
		ptr->infos = real->infos;
		ptr->amount = real->amount;
		free(real);
	}
	else {
	    t_free_node(ptr);
	    free(ptr);
	}
	return OK;
}


short t_find_next(Tree* tree, Node* ptr, Node** dest)
{
	if (ptr->right) {
		ptr = ptr->right;
		while (ptr->left)
			ptr = ptr->left;
		*dest = ptr;
		return OK;
	}
	Node* parent = ptr->parent;
	while (parent) {
		if (parent->left == ptr) {
			*dest = parent;
			return OK;
		}
		ptr = parent;
		parent = ptr->parent;
	}
	return -1;
}


short t_find(Tree* tree, unsigned int key, Node** dest)
{
	if (!tree->root)
		return -2;

	Node *ptr = tree->root, *parent;
	while (ptr) {
		parent = ptr;
		if (key == ptr->key) {
			*dest = ptr;
			return OK;
		}
		if (key < ptr->key)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	*dest = parent;
	return -1;
}


short t_special_search(Tree* tree, unsigned int key, Node** dest)
{
	if (!tree->root)
		return -2;

	Node *ptr = tree->root;
	while (ptr->left && ptr->left->key > key) { // ищем слева первый ключ меньше нужного
		ptr = ptr->left;
	}
	if (!ptr->left) // не нашли слева ключ меньше нужного => его и нет вовсе
		return -1;
	if (ptr->key > key)
		ptr = ptr->left; // нашли первый ключ меньше нужного

	Node* max;
	while (ptr) {
		// идём по возрастанию, пока можем
		while (ptr->right && ptr->right->key <= key) {
			ptr = ptr->right;
		}
		if (!ptr->right) { // дошли до упора - больше уже не будет
			*dest = ptr;
			return OK;
		}
		max = ptr; // запомнили
		ptr = ptr->right; // перешли на ключ, больший чем нужно

		// идём от него влево, пока не выйдем снова в "безопасную зону"
		while (ptr->left && ptr->left->key > key) {
			ptr = ptr->left;
		}
		if (!ptr->left) { // дошли до упора и не вышли в безопасную зону => max - наш нужный ключ
			*dest = max;
			return OK;
		}
		ptr = ptr->left; // вышли в безопасную зону. снова идём вправо
	}
	return 18649; // never reaches this line
}


void t_inOrder_traversal(Tree* tree, unsigned int key)
{
	if (t_is_empty(tree)) {
		printf("The tree is empty\n");
		return;
	}
	int h = 0;
	int i;
	Node* ptr = tree->root;
	printf("height - key - infos\n");
	while (ptr) {
		if (ptr->left && !(ptr->printed & 2)) {
			ptr->printed |= 2;
			ptr = ptr->left;
			h++;
			continue;
		}
		// забавно, что можно даже написать не key != -1, а key < -1
		if (key != -1 && ptr->key <= key)
			ptr->printed |= 4;

		if (!(ptr->printed & 4)) {
			printf("%d\t%u - ", h, ptr->key);
			for (i = 0; i < ptr->amount - 1; i++)
				printf("%s,  ", ptr->infos[i]);
			printf("%s\n", ptr->infos[i]);
			ptr->printed |= 4;
		}
		if (ptr->right && !(ptr->printed & 1)) {
			ptr->printed |= 1;
			ptr = ptr->right;
			h++;
			continue;
		}
		ptr->printed = 0;
		ptr = ptr->parent;
		h--;
	}
}


void t_preOrder_traversal(Tree* tree, unsigned int key)
{
	if (t_is_empty(tree)) {
		printf("The tree is empty\n");
		return;
	}
	int h = 0;
	int i;
	Node* ptr = tree->root;
	printf("height - key - infos\n");
	while (ptr) {
		if (key != -1 && ptr->key <= key)
			ptr->printed |= 4;

		if (!(ptr->printed & 4)) {
			printf("%d\t%u - ", h, ptr->key);
			for (i = 0; i < ptr->amount - 1; i++)
				printf("%s,  ", ptr->infos[i]);
			printf("%s\n", ptr->infos[i]);
			ptr->printed |= 4;
		}
		if (ptr->left && !(ptr->printed & 2)) {
			ptr->printed |= 2;
			ptr = ptr->left;
			h++;
			continue;
		}
		if (ptr->right && !(ptr->printed & 1)) {
			ptr->printed |= 1;
			ptr = ptr->right;
			h++;
			continue;
		}
		ptr->printed = 0;
		ptr = ptr->parent;
		h--;
	}
}


void t_postOrder_traversal(Tree* tree, unsigned int key)
{
	if (t_is_empty(tree)) {
		printf("The tree is empty\n");
		return;
	}
	int h = 0;
	int i;
	Node* ptr = tree->root;
	printf("height - key - infos\n");
	while (ptr) {
		if (ptr->left && !(ptr->printed & 2)) {
			ptr->printed |= 2;
			ptr = ptr->left;
			h++;
			continue;
		}
		if (ptr->right && !(ptr->printed & 1)) {
			ptr->printed |= 1;
			ptr = ptr->right;
			h++;
			continue;
		}
		if (key != -1 && ptr->key <= key)
			ptr->printed |= 4;

		if (!(ptr->printed & 4)) {
			printf("%d\t%u - ", h, ptr->key);
			for (i = 0; i < ptr->amount - 1; i++)
				printf("%s,  ", ptr->infos[i]);
			printf("%s\n", ptr->infos[i]);
			ptr->printed |= 4;
		}
		ptr->printed = 0;
		ptr = ptr->parent;
		h--;
	}
}


short t_is_empty(Tree* tree)
{
	return tree->root == NULL;
}


int t_get_height(Tree* tree)
{
	if (t_is_empty(tree)) {
		return 0;
	}
	int h = 0, maxh = 0;
	Node* ptr = tree->root;
	while (ptr) {
		if (ptr->left && !(ptr->printed & 2)) {
			ptr->printed |= 2;
			ptr = ptr->left;
			h++;
			if (h > maxh) maxh = h;
			continue;
		}
		if (ptr->right && !(ptr->printed & 1)) {
			ptr->printed |= 1;
			ptr = ptr->right;
			h++;
			if (h > maxh) maxh = h;
			continue;
		}
		ptr->printed = 0;
		ptr = ptr->parent;
		h--;
	}
	return maxh;
}

// сколько вершин ниже по дереву (выше по номеру)
int get_subtree_amount(int height, int maxheight)
{
	// int amount = 2 ** (maxheight + 1) - 1; // всего вершин в дереве
	// amount = amount - 2 ** height + 1; // вычли вершины выше текущей
	// amount /= 2 ** height; // оставили только одно поддерево нужной высоты
	// amount -= 1; // вычли саму вершину
	// return amount;
	int amount = 0;
	int two = 2;
	for (int i = 1; i < maxheight - height + 1; i++) {
		amount += two;
		two *= 2;
	}
	return amount;
}


void t_count(Tree* tree)
{
	Node* ptr = tree->root;
	printf("key - amount\n");
	while (ptr) {
		if (!(ptr->printed & 4)) {
			printf("%u - %u\n", ptr->key, ptr->amount);
			ptr->printed |= 4;
		}
		if (ptr->left && !(ptr->printed & 2)) {
			ptr->printed |= 2;
			ptr = ptr->left;
			continue;
		}
		if (ptr->right && !(ptr->printed & 1)) {
			ptr->printed |= 1;
			ptr = ptr->right;
			continue;
		}
		ptr->printed = 0;
		ptr = ptr->parent;
	}
}

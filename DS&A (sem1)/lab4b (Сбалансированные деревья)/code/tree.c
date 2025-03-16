#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tree.h"
#include "queue.h"

#define OK 0
#define MEMORY 4
#define TREE_EMPTY -2
#define TREE_NOTFOUND -1
#define TREE_DUPLICATE -1

struct Tree {
	Node* root;
	double alpha;
	unsigned int size;
	unsigned int maxsize;
};


short t_create(Tree** dest)
{
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	if (tree == NULL)
		return MEMORY;

	double alpha = 0.555;
	*tree = (Tree){NULL, alpha, 0, 0};
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
	free(node->key);
	node->key = NULL;
}


void t_print_console_type1(Tree* tree)
{
	if (t_is_empty(tree)) {
		printf("The tree is empty\n");
		return;
	}
	unsigned int h = 0, maxh = t_get_maxheight(tree);
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
			printf("\"%s\" - %u\n", ptr->key, ptr->info);
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
		return MEMORY;
	checker = q_insert(que, tree->root, 0, "");
	if (checker) {
		free(que);
		return MEMORY;
	}
	int currLevel = 0;
	QueueNode quenode;

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
	printf("%s┌──\"%s\" - %u\n", prefix, treeNode->key, treeNode->info);

	char newPrefix[1024];
	if (treeNode->left) {
		snprintf(newPrefix, sizeof(newPrefix), "%s.\t", prefix);
	    checker = q_insert(que, treeNode->left, level + 1, newPrefix);
	    if (checker) {
			free(prefix);
			q_free(que);
			free(que);
		return MEMORY;
	    }
	}
	if (treeNode->right) {
	    snprintf(newPrefix, sizeof(newPrefix), "%s|\t", prefix);
	    checker = q_insert(que, treeNode->right, level + 1, newPrefix);
	    if (checker) {
			free(prefix);
			q_free(que);
			free(que);
		return MEMORY;
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
			fprintf(file, "%s\n%u\n", ptr->key, ptr->info);
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


short t_insert(Tree* tree, KeySpace ks, unsigned int* previnfo)
{
	Node* last = NULL;
	unsigned int height;
	short checker = t_insert_common(tree, ks, &last, &height, previnfo);
	if (checker) return checker;

	unsigned int maxh = (int)logarithm(tree->size, (double) 1 / tree->alpha) + 1;
	if (height > maxh) {
		Node* scapegoat = t_find_theGOAT(last, tree->alpha);
		if (scapegoat) {
			checker = t_rebuildTree(tree, scapegoat);
			if (checker) return checker;
		}
	}
	return OK;
}


short t_insert_common(Tree* tree, KeySpace ks, Node** last, unsigned int* height, unsigned int* previnfo)
{
	Node new = (Node){ks.key, ks.info, NULL, NULL, NULL, 0};
	if (!tree->root) {
		Node* node = (Node*)malloc(sizeof(Node));
		if (!node)
			return MEMORY;
		*node = new;
		tree->root = node;
		tree->size = 1;
		if (tree->size > tree->maxsize) tree->maxsize = tree->size;
		*last = node;
		*height = 1;
		return OK;
	}
	Node* ptr;
	short checker = t_find(tree, ks.key, &ptr, height);

	if (checker == OK) {
		if (ptr->key != ks.key)
			free(ptr->key);
		ptr->key = ks.key; // чтобы не потерять ks.key,
		// т.к. при дублировании ks.key никуда не записывался бы
		*previnfo = ptr->info;
		ptr->info = ks.info;
		return -1;
	}

	Node* node = (Node*)malloc(sizeof(Node));
	if (!node)
		return MEMORY;
	*node = new;
	node->parent = ptr;
	if (strcmp(ks.key, ptr->key) < 0)
		ptr->left = node;
	else
		ptr->right = node;

	tree->size++;
	if (tree->size > tree->maxsize) tree->maxsize = tree->size;
	*last = node;
	return OK;
}


Node* t_find_theGOAT(Node* last, double alpha)
{
	Node* ptr = last;
	while (ptr) {
		if (!t_is_balanced(ptr, alpha))
			return ptr;
		ptr = ptr->parent;
	}
	return NULL;
}


short t_is_balanced(Node* hostage, double alpha)
{
	unsigned int size_left = t_getSize(hostage->left);
	unsigned int size_right = t_getSize(hostage->right);
	unsigned int size_parent = size_left + size_right + 1;
	if (size_left <= alpha * size_parent && size_right <= alpha * size_parent)
		return 1;
	return 0;
}


unsigned int t_getSize(Node* node)
{
	if (!node) return 0;

	unsigned int size = 0;
	Node *ptr = node, *parent = node->parent;
	while (ptr != parent) {
		if (ptr->left && !(ptr->printed & 2)) {
			ptr->printed |= 2;
			ptr = ptr->left;
			continue;
		}
		if (!(ptr->printed & 4)) {
			size++;
			ptr->printed |= 4;
		}
		if (ptr->right && !(ptr->printed & 1)) {
			ptr->printed |= 1;
			ptr = ptr->right;
			continue;
		}
		ptr->printed = 0;
		ptr = ptr->parent;
	}
	return size;
}


short t_rebuildTree(Tree* tree, Node* goat)
{
	unsigned int goatSize = t_getSize(goat);

	Node* goatParent = goat->parent;
	short goatSide = goatParent ? (goatParent->left == goat ? 1 : -1) : 0;

	Node** goatTree;
	short checker = t_rebuild_traversal(goat, &goatTree, goatSize);
	if (checker) return checker;

	Node* first = t_buildSubtree(0, goatSize - 1, goatTree);
	if (goatSide == 1) goatParent->left = first;
	else if (goatSide == -1) goatParent->right = first;
	else tree->root = first;
	first->parent = goatParent;

	free(goatTree);
	return OK;
}


short t_rebuild_traversal(Node* goat, Node*** dest, unsigned int size)
{
	Node** goatTree = (Node**)malloc(sizeof(Node*) * size);
	if (!goatTree) return MEMORY;

	Node *ptr = goat, *parent, *goatParent = goat->parent;
	unsigned int count = 0;
	while (ptr != goatParent) {
		if (ptr->left && !(ptr->printed & 2)) {
			ptr->printed |= 2;
			ptr = ptr->left;
			continue;
		}
		if (!(ptr->printed & 4)) {
			goatTree[count] = ptr;
			count++;
			ptr->printed |= 4;
		}
		if (ptr->right && !(ptr->printed & 1)) {
			ptr->printed |= 1;
			ptr = ptr->right;
			continue;
		}
		ptr->printed = 0;
		ptr->left = NULL;
		ptr->right = NULL;
		parent = ptr->parent;
		ptr->parent = NULL;
		ptr = parent;
	}

	*dest = goatTree;
	return OK;
}


Node* t_buildSubtree(int start, int end, Node** goatTree)
{
	if (start > end)
		return NULL;

	int mid = (end + start) / 2;

	Node* root = goatTree[mid];

	root->left = t_buildSubtree(start, mid - 1, goatTree);
	if (root->left) root->left->parent = root;

	root->right = t_buildSubtree(mid + 1, end, goatTree);
	if (root->right) root->right->parent = root;

	return root;
}


short t_delete(Tree* tree, char* key)
{
	short checker = t_delete_common(tree, key);
	if (checker) return checker;

	if (tree->size < tree->alpha * tree->maxsize) {
		checker = t_rebuildTree(tree, tree->root);
		if (checker) return checker;
		tree->maxsize = tree->size;
	}
	return OK;
}


short t_delete_common(Tree* tree, char* key)
{
	Node* ptr;
	unsigned int height;
	short checker = t_find(tree, key, &ptr, &height);
	if (checker) {
		return checker;
	}

	Node *real = ptr;
	if (ptr->left && ptr->right)
		t_find_next(ptr, &real);
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
		ptr->info = real->info;
		free(real);
	}
	else {
	    t_free_node(ptr);
	    free(ptr);
	}
	return OK;
}


short t_find_next(Node* ptr, Node** dest)
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
	return TREE_NOTFOUND;
}


short t_find(Tree* tree, char* key, Node** dest, unsigned int* height)
{
	if (!tree->root)
		return TREE_EMPTY;

	unsigned int h = 1;
	Node *ptr = tree->root, *parent;
	while (ptr) {
		parent = ptr;
		if (strcmp(key, ptr->key) == 0) {
			*dest = ptr;
			*height = h;
			return OK;
		}
		if (strcmp(key, ptr->key) < 0)
			ptr = ptr->left;
		else
			ptr = ptr->right;
		h++;
	}
	*dest = parent;
	*height = h;
	return TREE_NOTFOUND;
}


short t_special_search(Tree* tree, char* key, Node** dest)
{
	if (!tree->root)
		return TREE_EMPTY;

	Node *ptr = tree->root;
	while (ptr->left && strcmp(ptr->left->key, key) > 0) { // ищем слева первый ключ меньше нужного
		ptr = ptr->left;
	}
	if (!ptr->left) // не нашли слева ключ меньше нужного => его и нет вовсе
		return TREE_NOTFOUND;
	if (strcmp(ptr->key, key) > 0)
		ptr = ptr->left; // нашли первый ключ меньше нужного

	Node* max;
	while (ptr) {
		// идём по возрастанию, пока можем
		while (ptr->right && strcmp(ptr->right->key, key) <= 0) {
			ptr = ptr->right;
		}
		if (!ptr->right) { // дошли до упора - больше уже не будет
			*dest = ptr;
			break;
		}
		max = ptr; // запомнили
		ptr = ptr->right; // перешли на ключ, больший чем нужно

		// идём от него влево, пока не выйдем снова в "безопасную зону"
		while (ptr->left && strcmp(ptr->left->key, key) > 0) {
			ptr = ptr->left;
		}
		if (!ptr->left) { // дошли до упора и не вышли в безопасную зону => max - наш нужный ключ
			*dest = max;
			break;
		}
		ptr = ptr->left; // вышли в безопасную зону. снова идём вправо
	}
	return OK;
}


void t_inOrder_traversal(Tree* tree, char* key)
{
	if (t_is_empty(tree)) {
		printf("The tree is empty\n");
		return;
	}
	int h = 0;
	Node* ptr = tree->root;
	printf("height - key - infos\n");
	while (ptr) {
		if (ptr->left && !(ptr->printed & 2)) {
			ptr->printed |= 2;
			ptr = ptr->left;
			h++;
			continue;
		}
		if (*key != '\0' && strcmp(ptr->key, key) <= 0)
			ptr->printed |= 4;

		if (!(ptr->printed & 4)) {
			printf("%d\t\"%s\" - %u\n", h, ptr->key, ptr->info);
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


void t_preOrder_traversal(Tree* tree, char* key)
{
	if (t_is_empty(tree)) {
		printf("The tree is empty\n");
		return;
	}
	int h = 0;
	Node* ptr = tree->root;
	printf("height - key - infos\n");
	while (ptr) {
		if (*key != '\0' && strcmp(ptr->key, key) <= 0)
			ptr->printed |= 4;

		if (!(ptr->printed & 4)) {
			printf("%d\t\"%s\" - %u\n", h, ptr->key, ptr->info);
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


void t_postOrder_traversal(Tree* tree, char* key)
{
	if (t_is_empty(tree)) {
		printf("The tree is empty\n");
		return;
	}
	int h = 0;
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
		if (*key != '\0' && strcmp(ptr->key, key) <= 0)
			ptr->printed |= 4;

		if (!(ptr->printed & 4)) {
			printf("%d\t\"%s\" - %u\n", h, ptr->key, ptr->info);
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


unsigned int t_get_maxheight(Tree* tree)
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
unsigned int get_subtree_amount(unsigned int height, unsigned int maxheight)
{
	// int amount = 2 ** (maxheight + 1) - 1; // всего вершин в дереве
	// amount = amount - 2 ** height + 1; // вычли вершины выше текущей
	// amount /= 2 ** height; // оставили только одно поддерево нужной высоты
	// amount -= 1; // вычли саму вершину
	// return amount;
	unsigned int amount = 0;
	int two = 2;
	for (unsigned int i = 1; i < maxheight - height + 1; i++) {
		amount += two;
		two *= 2;
	}
	return amount;
}


double logarithm(double num, double base)
{
	return log(num) / log(base);
}

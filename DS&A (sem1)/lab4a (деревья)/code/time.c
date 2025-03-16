#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "treeTime.h"

struct Tree {
	Node* root;
};


Tree* tree_generate(int num_of_elems)
{
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	tree->root = NULL;

	srand(time(NULL));
	KeySpace ks;
	char gift[14] = "Initial value\0";

	for (int i = 0; i < num_of_elems; i++) {
		ks = (KeySpace){0, NULL};
		ks.key = rand() % 10000000;

		ks.info = (char*)malloc((strlen(gift) + 1) * sizeof(char));
		sprintf(ks.info, "%s", gift);

		t_insert(tree, ks);
	}

	return tree;
}


KeySpace* ksArr_generate(int capacity)
{
	KeySpace* arr = (KeySpace*)malloc(capacity * sizeof(KeySpace));

	srand(time(NULL));
	KeySpace ks;
	char gift[12] = "Added value\0";

	for (int i = 0; i < capacity; i++) {
		ks = (KeySpace){0, NULL};
		ks.key = rand() % 10000000;

		ks.info = (char*)malloc((strlen(gift) + 1) * sizeof(char));
		sprintf(ks.info, "%s", gift);

		arr[i] = ks;
	}

	return arr;
}


void treeTiming()
{
	printf("started!\n");
	clock_t begin, end;
	const int MAX_NUM = 100001, MIN_NUM = 100000, step = 100000, capacity = 2000;
	const int num_of_res = 25;

	for (int num_of_elems = MIN_NUM; num_of_elems < MAX_NUM; num_of_elems += step) {
		double insertions = 0.0, findings = 0.0, deletions = 0.0;

		for (int j = 0; j < num_of_res; j++) {
			printf("tree generating... (%d)\n", j);
			Tree* tree = tree_generate(num_of_elems);
			printf("ksArr generating... (%d)\n", j);
			KeySpace* ksArr = ksArr_generate(capacity);
			printf("data generated! (%d)\n", j);

			begin = clock();
			for (int i = 0; i < capacity; i++)
				t_insert(tree, ksArr[i]);
			end = clock();
			insertions += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);

			Node* temp;
			begin = clock();
			for (int i = 0; i < capacity; i++)
				t_find(tree, ksArr[i].key, &temp);
			end = clock();
			findings += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);

			begin = clock();
			for (int i = 0; i < capacity; i++)
				t_delete(tree, ksArr[i].key);
			end = clock();
			deletions += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);

			t_free(tree);
			free(tree);
			free(ksArr);
		}

		insertions /= num_of_res;
		findings /= num_of_res;
		deletions /= num_of_res;
		printf("\nNum of elements: %d\nTime on insert(): %f ms.\nTime on find(): %f ms.\nTime on delete(): %f ms.\n",
		num_of_elems, insertions, findings, deletions);
	}
}

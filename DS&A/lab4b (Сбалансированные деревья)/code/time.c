#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "treeTime.h"

struct Tree {
	Node* root;
};


Tree* tree_generate(int num_of_elems)
{
	Tree* tree;
	t_create(&tree);
	tree->root = NULL;

	srand(time(NULL));
	KeySpace ks;
	int gift = 5;
	int key_int;

	for (int i = 0; i < num_of_elems; i++) {
		ks = (KeySpace){NULL, 0};

		key_int = rand() % 10000000 + 1;
		ks.key = (char*)malloc((int)(log10(key_int) + 2) * sizeof(char));
		sprintf(ks.key, "%d", key_int);

		ks.info = gift;
		unsigned int temp;
		t_insert(tree, ks, &temp);
	}

	return tree;
}


KeySpace* ksArr_generate(int capacity)
{
	KeySpace* arr = (KeySpace*)malloc(capacity * sizeof(KeySpace));

	srand(time(NULL));
	KeySpace ks;
	char gift = 7;
	int key_int;

	for (int i = 0; i < capacity; i++) {
		int fl = 0;
		ks = (KeySpace){NULL, 0};

		key_int = rand() % 10000000 + 1;
		ks.key = (char*)malloc((int)(log10(key_int) + 2) * sizeof(char));
		sprintf(ks.key, "%d", key_int);

		// дублирование ключей запрещено, поэтому исключим его
		for (int j = 0; j < i; j++) {
			if (strcmp(arr[j].key, ks.key) == 0) {
				free(ks.key);
				i--;
				fl = 1;
				break;
			}
		}
		if (fl) continue;

		ks.info = gift;

		arr[i] = ks;
	}

	return arr;
}


void treeTiming()
{
	printf("started!\n");
	clock_t begin, end;
	const int MAX_NUM = 2000001, MIN_NUM = 100000, step = 100000, capacity = 2000;
	const int num_of_res = 25;

	for (int num_of_elems = MIN_NUM; num_of_elems < MAX_NUM; num_of_elems += step) {
		double insertions = 0.0, findings = 0.0, deletions = 0.0;

		for (int j = 0; j < num_of_res; j++) {
			// printf("tree generating... (%d)\n", j);
			Tree* tree = tree_generate(num_of_elems);
			// printf("ksArr generating... (%d)\n", j);
			KeySpace* ksArr = ksArr_generate(capacity);
			printf("data generated! (%d)\n", j);

			unsigned int tempint;
			begin = clock();
			for (int i = 0; i < capacity; i++)
				t_insert(tree, ksArr[i], &tempint);
			end = clock();
			insertions += (double)(end - begin) / (CLOCKS_PER_SEC / 1000);

			Node* temp;
			begin = clock();
			for (int i = 0; i < capacity; i++)
				t_find(tree, ksArr[i].key, &temp, &tempint);
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

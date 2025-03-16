#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mylib.h"


int is_valid_mask(const char *mask)
{
	while (*mask) {
		if (!isalpha(*mask) && *mask != '?') {
			return 0;
		}
		mask++;
	}
	return 1;
}


const char** words_from_mask(const char* mask)
{
	FILE *file = fopen("words.txt", "r");
	if (!file) {
		printf("Failed to open file\n");
		return NULL;
	}

	const char **words = NULL;
	size_t capacity = 0;
	size_t count = 0;
	char *word = NULL;
	size_t word_length = 0;

	while (getline(&word, &word_length, file) != -1) {
		word[strcspn(word, "\n")] = 0;

		if (is_match_to_mask(word, mask)) {
			if (count >= capacity) {
				capacity = capacity ? capacity * 2 : 1;
				words = realloc(words, capacity * sizeof(char*));
			}
			words[count] = strdup(word);
			count++;
		}
	}

	free(word);
	fclose(file);

	words = realloc(words, (count + 1) * sizeof(char*));
	words[count] = NULL;
	return words;
}


int is_match_to_mask(const char *word, const char *mask)
{
	while (*mask) {
		if (*mask != '?' && *mask != *word) {
			return 0;
		}
		mask++;
		word++;
	}
	return *word == '\0';
}

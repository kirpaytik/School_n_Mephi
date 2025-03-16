#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"


void dialogue_start()
{
	printf("Input a string template to search for words\n");
	const char *mask;
	while (1) {
		printf(">>> ");
		scanf("%m[^\n]%*c", &mask);

		if (!is_valid_mask(mask)) {
			printf("The string contains unrecognised symbols!\n");
			free((void *)mask);
			continue;
		}
		break;
	}

	const char** words;
	words = words_from_mask(mask);
	free((void *)mask);

	printf("Words that matches to template:\n");
	unsigned int i = 0;
	while (words[i]) {
		printf("\"%s\"\n", words[i]);
		free((void *)words[i]);
		i++;
	}

	free(words);
}

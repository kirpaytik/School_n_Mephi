#include "funny.h"
#include <stdlib.h>
#include <string.h>

int is_big(char bukva) {
		return (int) ((bukva >= 'A') && (bukva <= 'Z'));
}

char* process2 (char* string)
{
	char* str = malloc(sizeof(char));
	int len1 = strlen(string);
	int len2 = 0;
	int i;
	for (i = 0; i< len1; i++) {
		len2++;
		str = realloc(str, len2*sizeof(char));
		str[len2-1] = string[i];
		if (is_big(string[i])) {
			len2++;
			str = realloc(str, len2*sizeof(char));
			str[len2-1] = string[i];
		}
	}
	len2++;
	str = realloc(str, len2*sizeof(char));
	str[len2-1] = '\0';
	return str;
}
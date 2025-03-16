#include "funny.h"
#include <stdlib.h>
#include <string.h>

void process1 (int** array, int* size)
{
	for (int i=0; i < *size; i++) {
		if (*(*array + i) > 9) {
			(*size)++;
			*array = realloc(*array, (*size)*sizeof(int));
			for (int j=*size - 1; j > i; j--) {
				*(*array + j) = *(*array + j - 1);
			}
			int chislo = *(*array + i);
			*(*array +i+1) = chislo % 10;
			*(*array + i) /= 10;
			i--;
		}
	}
	return;
}

int is_big(char bukva) {
		return (int) ((bukva >= 'A') && (bukva <= 'Z'));
}

char* process2 (char* string) {
	char* neww = calloc(1, 1);
	int lenn = strlen(string);
	int new_len = 0;
	for (int i = 0; i < lenn; i++) {
		new_len++;
		neww = realloc(neww, new_len*sizeof(char));
		neww[new_len-1] = string[i];
		if (is_big(string[i])) {
			new_len++;
			neww = realloc(neww, new_len*sizeof(char));
			neww[new_len-1] = string[i];
		}
	}
	new_len++;
	neww = realloc(neww, new_len*sizeof(char));
	neww[new_len-1] = '\0';
	return neww;
}

// то, как я написал на кр, неверно. задание было другим: перевернуть порядок слов
char* process22 (char* string) {
	int len = strlen(string);
	char string2[len];
	strcpy(string, string2);
	
	char str1[len];
	char str2[len];
	strcpy(str1, "");
	strcpy(str2, "");
	
	char *token = strtok(string2, " ");
	strcpy(str2, token);
	token = strtok(NULL, " ");
	while (token != NULL) {
		strcat(str1, token);
		strcat(str1, " ");
		strcpy(str1, str2);
		
		strcpy(str2, str1);
		token = strtok(NULL, " ");
	}
	return str2; // warning: function returns address of local variable
	// короче, если объявить через malloc(), то он не почистит ничего,
	// а если через [], то после выхода из функции переменная будет очищена,
	// и в main поступит ничего
}

void process3(List* orig)
{
        Node* elem = orig->head;
        Node* first = elem;
        int sum = 0, amount = 0;
        while (elem->next != first) {
                sum += elem->data;
                amount++;
                elem = elem->next;
        }
        sum += elem->data;
        amount++;
        elem = elem->next;
        double sredn = ((double) sum)/(amount);
        do {
                if ((elem->next)->data < sredn) {
                        Node* old_next = elem->next;
                        if (old_next == first) {
                                first = old_next->next;
                                orig->head = old_next->next;
                        }
                        elem->next = old_next->next;
                        free(old_next);
                }
        } while (elem->next != first);
}
#include <stdio.h>
#include <stdlib.h>
#include "mystringh.h"

int slen (char *s)
{
    int i=0;
    while (s[i] != '\0') {i++;}

    return i;
}

void scpy (char *dest, char *src) // предполагается, что длина dest >= длина src
{
    int lens = slen(src);
    int i;
    for (i = 0; i < lens+1; i++) {
        dest[i] = src[i];
    }
}

void scat (char *dest, char *src)
{
    int lend = slen(dest);
    int lens = slen(src);
    int i;
    for (i = 0; i < lens+1; i++) {
        dest[lend + i] = src[i];
    }
}

char *readl(char *s)
{
    printf(s);

    char *ptr = (char*)malloc(1);
    *ptr = '\0';
    char buf[81];
    int n, len=0;

    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            free(ptr);
            ptr = NULL;
            continue;
        }
        if (n == 0) {
            scanf("%*c");
        }
        else {
            len += slen(buf);
            ptr = (char*)realloc(ptr, len+1);
            scat(ptr, buf);
        }
    } while (n > 0);

    return ptr;
}

char *stok (char *s, char *delim)
{
    static char *s2 = NULL;
    char *token = NULL;

    if (s != NULL) {
        s2 = s;
    }

    int del_amm = slen(delim);
    int fl, fl2;
    int j;
    fl = 1; fl2 = 0; // fl = "s[i] - буква", fl2 = "ранее уже нашли букву"
    while (s2 != NULL && *s2 != '\0') {
        for (j = 0; j < del_amm; j++) {
            if (*s2 == delim[j]) {
                fl = 0;
            }
        }
        if (fl2 == 0) { // ещё не нашли букву ранее
            if (fl == 0) { // s[i] - пробел
                *s2 = '\0';
                fl = 1; // ресет флага перед новым циклом
            }
            else { // fl == 1; s[i] - буква
                fl2 = 1; // нашли первую букву
                token = s2;
            }
        }
        else /*fl2 == 1*/ if (fl == 0) { // после нахождения первой буквы снова нашли пробел
            *s2 = '\0';
            s2++;
            return token;
        }

        s2++;
    }
    if (s2 != NULL) {
        s2 = NULL;
        return token;
    }

    return NULL; // if s2 == NULL
}

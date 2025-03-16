// здесь без некоторых исправлений в отдельных main.c и myfuncs.c
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

#define space " "
#define tab "\t"
#define spacetab " \t"

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

int safeScanfInt (int *target)
{
    int guard;
    int flag = 1;
    while (flag == 1) {
        guard = scanf("%d",target);
        scanf("%*[^\n]");
        scanf("%*c");
        if (guard == EOF) {
            return 0;
        }
        if (guard < 1) {
            printf("Please input an integer number!\n");
            continue;
        }
        flag = 0;
    }
    return 1;
}

void loop_left(char *s, int n)
{
    int lens = slen(s);
    int i;
    if (n > 0) { // сдвиг влево
        s[lens] = s[0];
        for (i = 0; i < lens; i++) {
            s[i] = s[i+1];
        }
        s[lens] = '\0';
    }

    else { // сдвиг вправо
        for (i = lens; i > 0; i--) {
            s[i] = s[i-1];
        }
        s[0] = s[lens];
        s[lens] = '\0';
    }
}

void func(char *s, int n)
{
    int lens = slen(s);
    while (s[0] == space[0] || s[0] == tab[0]) {
        loop_left(s, 1);
        s[lens-1] = '\0';
        lens--;
    }
    
    char s2[lens];
    scpy(s2, s);
    scpy(s, "");

    char *token;
    token = stok(s2, spacetab);
    int i;
    while (token != NULL) {
        for (i = 0; i < abs(n); i++) {
            loop_left(token, n);
        }
        strcat(s, token);
        token = strtok(NULL, spacetab);
        if (token != NULL) {
            strcat(s, space);
        }
    }
    // s[lens] = '\0'; // т.к. длина выходной строки та же, что и у начальной, то просто [lens]
    // кхм-кхм... во-первых пред. строка вовсе не нужна
    // а во-вторых ЧТО ЗА БРЕД, АХАХАХА
    // free(s2);
}



int main()
{
    char *stroka = NULL;
    int number;
    int fl;
    do {
        stroka = readl("Input a string\n");
        printf("\n");
        if (stroka == NULL || slen(stroka) == 0) {
            break;
        }

        printf("Input a number\n");
        fl = safeScanfInt(&number);
        printf("\n");
        if (fl == 0) {
            break;
        }

        func(stroka, number);
        printf("Output string:\n");
        printf("\"%s\"\n\n", stroka);
    } while (stroka != NULL && fl != 0);

    printf("Ending the program\n");
    free(stroka);
    return 0;
}

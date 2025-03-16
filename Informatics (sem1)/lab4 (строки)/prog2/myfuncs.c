#include <stdio.h>
#include <stdlib.h>
#include "myfuncs.h"
#include "mystringh.h"

#define space " "
#define tab "\t"
#define spacetab " \t"

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


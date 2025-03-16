// здесь без некоторых исправлений в отдельных main.c и myfuncs.c
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

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
    int lens = strlen(s);
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
    int lens = strlen(s);
    while (s[0] == space[0] || s[0] == tab[0]) {
        loop_left(s, 1);
        s[lens-1] = '\0';
        lens--;
    }
    
    char s2[lens];
    strcpy(s2, s);
    strcpy(s, "");

    char *token;
    token = strtok(s2, spacetab);
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
        stroka = readline("Input a string\n");
        printf("\n");
        if (stroka == NULL || strlen(stroka) == 0) {
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

char *readl(char *s)
{
    printf("%s", s);

    char *ptr = (char*)malloc(1);
    *ptr = '\0';
    char buf[81];
    int n=0, len=0;
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
            len += strlen(buf);
            char *temp = (char*)realloc(ptr, (len+1)*sizeof(char));
            if (temp == NULL) {
                free(ptr);
                return NULL;
            }
            ptr = temp;
            strcat(ptr, buf);
        }
    } while (n > 0);

    return ptr;
}

// как я написал в гайде по фришкам, иногда valgrind ругается на realloc (даже в оригинальном readline)
// в тот раз у меня это было связано с тем, что описано в том же гайде по фришкам
#include <stdlib.h>
#include <readline/readline.h>
#include "ffunc.h"

int main()
{
    char *sstr;
    int fl = 1;
    while (fl) { // fl = 1 always
        sstr = readline("Введите строку.\n");
        if (sstr == NULL) {
            printf("Завершение программы.");
            break;
        }
        
        ffunc(sstr);
        printf("%s\n", sstr);
        free(sstr);
    }
    
    return 0;
}

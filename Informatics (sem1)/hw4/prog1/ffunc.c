#include <string.h>
#include "ffunc.h"

void ffunc(char *sstr)
{
    int i;
    int len = strlen(sstr);
    
    if (sstr[0] != ' ') {
        for (i = 0; i < len - 1; ++i) {
            sstr[i] = sstr[i+1];
        }
        sstr[len-1] = '\0';
        len--;
    }
    
    int j;
    for (i = 1; i < len; ++i) {
        if (sstr[i-1] == ' ') {
            for (j = i; j < len - 1; ++j) {
                sstr[j] = sstr[j+1];
            }
            sstr[len-1] = '\0';
            len--;
        }
    }
}

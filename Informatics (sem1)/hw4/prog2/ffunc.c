#include <stdlib.h>
#include <string.h>
#include "ffunc.h"

void ffunc(char *sstr)
{
        int l = strlen(sstr);
        char sttr[l], strr[l];
        strcpy(sttr,sstr);
        strcpy(strr,sstr);

        strcpy(sstr,"");

        char *token = strtok(sttr, " ");
        while (token != NULL) {
                if (strlen(token) % 2 == 0) {
                        strcat(sstr, token);
                        strcat(sstr, " ");
                }
                token = strtok(NULL, " ");
        }

        token = strtok(strr, " ");
        while (token != NULL) {
                if (strlen(token) % 2 == 1) {
                        strcat(sstr, token);
                        strcat(sstr, " ");
                }
                token = strtok(NULL, " ");
        }
        // free(sttr);
        // free(strr);
}

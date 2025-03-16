#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "intFlComp.h"

int intFlComp (double number)
{
    double doppelIntN;
    double doppelFloatN;
    doppelFloatN = modf(number,&doppelIntN);
    int intN = (int)doppelIntN;
    
    // printf("%lf\n%d %lf\n", number, intN, floatN);
    if (intN == 0) {
        if (number != 0) {
            return 1;
        }
        else {
            return 0;
        }
    }

    int lenIntN = (int)floor(log10(abs(intN))) + 1;
    // printf("%d\n",lenIntN);
    int i;
    for (i = 0; i < lenIntN; i++) {
        doppelFloatN *= 10;
    }
    int floatN = (int)round(doppelFloatN);
    // printf("%d %lf %d\n", intN, doppelFloatN, floatN);
    if (abs(floatN) > abs(intN)) {
        return 1;
    }
    return 0;
}
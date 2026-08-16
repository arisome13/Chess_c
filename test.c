
#include <stdio.h>
#include "mask.h"

int main () {
    Mask_T oMask = Mask_new("p");
    Square_T oSqr1 = Square_initCoords(0, 5);
    Square_T oSqr2 = Square_initNotation("b5");

    Mask_place(oMask, oSqr1);
    Mask_place(oMask, oSqr2);
    Mask_capture(oMask, oSqr2);
    
    printf("%s\n", Mask_toString(oMask));
    
    Mask_free(oMask);
    Square_free(oSqr1);
    Square_free(oSqr2);
}

#include <stdio.h>
#include "movepattern.h"

int main (void) {
    MovePattern_T oPattern = MovePattern_new();
    MovePattern_add(oPattern, 0, 1, false);
    MovePattern_add(oPattern, 0, -1, false);
    MovePattern_add(oPattern, 1, 0, false);
    MovePattern_add(oPattern, -1, 0, false);

    char *str = MovePattern_toString(oPattern);
    printf("\' %s \'\n", str);
    free(str);
    
    MovePattern_free(oPattern);
}
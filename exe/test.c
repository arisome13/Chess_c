
#include <stdio.h>
#include "movepattern.h"

int main (void) {
    char *str;
    MovePattern_T tempMP;
    Square_T start = Square_newNotation("e2");

    tempMP = MovePattern_for('P');
    str = MovePattern_showMovesFrom(tempMP, start);
    printf("Pawn\n%s\n", str);
    MovePattern_free(tempMP);
    free(str);
    
    Square_free(start);
}
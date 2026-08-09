
#include <stdio.h>
#include "parameters.h"

int main () {
    ChessParameters_T parms = ChessParameters_new("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    printf("%s", ChessParameters_toString(parms));
    ChessParameters_free(parms);
}
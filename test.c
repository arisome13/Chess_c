
#include <stdio.h>
#include "board.h"

int main () {
    ChessBoard_T oBoard = ChessBoard_new("");

    printf("%s\n", ChessBoard_toString(oBoard));
    
    ChessBoard_free(oBoard);
}
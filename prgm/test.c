
#include <stdio.h>
#include "board.h"

int main (void) {
    ChessBoard_T oBoard = ChessBoard_new(STARTING_FEN);

    printf("%s\n", ChessBoard_toString(oBoard));
    
    ChessBoard_free(oBoard);
}
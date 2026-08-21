
#include <stdio.h>
#include "board.h"

int main (void) {
    ChessBoard_T oBoard = ChessBoard_new("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    printf("%s\n", ChessBoard_toString(oBoard));
    
    ChessBoard_free(oBoard);
}
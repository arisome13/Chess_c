/*--------------------------------------------------------------------*/
/* board.c                                                       */
/*--------------------------------------------------------------------*/

#include "board.h"
#include <assert.h>

struct ChessBoard
{
   /* */
   Mask_T mPieceMasks[MAX_PIECE_TYPES];
};

ChessBoard_T ChessBoard_new(const char *pcFen) {
    ChessBoard_T oBoard;

    assert(pcFen != NULL);

    oBoard = (ChessBoard_T)calloc(1, sizeof(struct ChessBoard));
    if (oBoard == NULL)
        return oBoard;

    /* must initialize bitmasks */

    return oBoard;
}

void ChessBoard_free(ChessBoard_T oBoard) {
    assert(oBoard != NULL);

    /* must free bitmasks */

    free(oBoard);
}

char *ChessBoard_strRep(ChessBoard_T oBoard) {
    assert(oBoard != NULL);

    return "hello world";
}


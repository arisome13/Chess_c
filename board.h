/*--------------------------------------------------------------------*/
/* board.h                                                       */
/*--------------------------------------------------------------------*/

#include <stdint.h>

#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include "mask.h"

enum {MAX_PIECE_TYPES = 64};

/* A ChessBoard_T object holds the piece positions on a chess board. */
struct ChessBoard
{
   /* */
   Mask_T mPieceMasks[MAX_PIECE_TYPES];
};
typedef struct ChessBoard *ChessBoard_T;

/*--------------------------------------------------------------------*/

/* Return a new ChessBoard_T object initialized to the fen chess
   layout, or NULL if insufficient memory is available. */
ChessBoard_T ChessBoard_new(char *pcFen);

/* Free oBoard. */
void ChessBoard_free(ChessBoard_T oBoard);

/* Return the string representation of oBoard. */
char *ChessBoard_strRep(ChessBoard_T oBoard);

#endif

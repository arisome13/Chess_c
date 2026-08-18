/*--------------------------------------------------------------------*/
/* board.h                                                       */
/*--------------------------------------------------------------------*/

#include <stdint.h>

#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include "mask.h"
#include "color.h"
#include "type.h"

enum {MAX_PIECE_TYPES = 64};

/* A ChessBoard_T object holds the piece positions on a chess board. */
typedef struct ChessBoard *ChessBoard_T;

/*--------------------------------------------------------------------*/

/* Return a new ChessBoard_T object initialized to the fen chess
   layout, or NULL if insufficient memory is available. */
ChessBoard_T ChessBoard_new(const char *pcFen);

/* Free oBoard. */
void ChessBoard_free(ChessBoard_T oBoard);

/* Return the string representation of oBoard. Caller must free. */
char *ChessBoard_toString(ChessBoard_T oBoard);

#endif

/*--------------------------------------------------------------------*/
/* board.h                                                       */
/*--------------------------------------------------------------------*/

#include <stdint.h>

#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include "mask.h"
#include "color.h"
#include "type.h"

/* A ChessBoard_T object holds the piece positions on a chess board. */
typedef struct ChessBoard *ChessBoard_T;

/*--------------------------------------------------------------------*/

/* Return a new ChessBoard_T object initialized to the fen chess
   layout. Caller must free. */
ChessBoard_T ChessBoard_new(const char *pcFen);

/* Free oBoard. */
void ChessBoard_free(ChessBoard_T oBoard);

/* Return a deep copy of oBoard. Caller must free. */
ChessBoard_T ChessBoard_copy(ChessBoard_T oBoard);

/*--------------------------------------------------------------------*/

/* Set up oBoard's masks to match pcFen. */
void ChessBoard_setFen(ChessBoard_T oBoard, const char *pcFen);

/* Return the mask from oBoard matching cName. */
Mask_T ChessBoard_getMask(ChessBoard_T oBoard, char cName);

/* Preforms the function 'func' on each mask in oBoard. */
void ChessBoard_onEachMask(ChessBoard_T oBoard, MaskFunction func, int *data);

/*--------------------------------------------------------------------*/

/* Return the string representation of oBoard. Caller must free. */
char *ChessBoard_toString(ChessBoard_T oBoard);

#endif

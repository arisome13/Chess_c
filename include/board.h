/*--------------------------------------------------------------------*/
/* board.h                                                            */
/*--------------------------------------------------------------------*/

#include <stdint.h>

#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include "map.h"
#include "move.h"
#include "results.h"
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

/* Set up oBoard's maps to match pcFen. */
void ChessBoard_setFen(ChessBoard_T oBoard, const char *pcFen);

/* Return the map from oBoard matching cName. */
Map_T ChessBoard_getMap(ChessBoard_T oBoard, char cName);

/* Preforms the function 'func' on each map in oBoard. */
void ChessBoard_onEachMap(ChessBoard_T oBoard, MapFunction func, int *data);

/* Tries to perform oMove on oBoard. Returns SUCCESS and changes the 
   board appropriately if the move was valid. Returns FAIL and doesn't
   change the board if the move was invalid. */
r_move ChessBoard_tryMove(ChessBoard_T oBoard, Move_T oMove);

/*--------------------------------------------------------------------*/

/* Return the string representation of oBoard. Caller must free. */
char *ChessBoard_toString(ChessBoard_T oBoard);

#endif

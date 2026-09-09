/*--------------------------------------------------------------------*/
/* board.h                                                            */
/*--------------------------------------------------------------------*/

#include "map.h"
#include "move.h"
#include "results.h"

#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

/* A ChessBoard_T object holds the piece positions on a chess board. */
typedef struct ChessBoard *ChessBoard_T;

/*--------------------------------------------------------------------*/

/* Return a new ChessBoard_T object initialized to the fen chess
   layout. CALLER FREE. */
ChessBoard_T ChessBoard_new(const char *pcFen);

/* Free oBoard. */
void ChessBoard_free(ChessBoard_T oBoard);

/* Return a deep copy of oBoard. CALLER FREE. */
ChessBoard_T ChessBoard_copy(ChessBoard_T oBoard);

/*--------------------------------------------------------------------*/

/* Set up oBoard's maps to match pcFen. */
void ChessBoard_setFen(ChessBoard_T oBoard, const char *pcFen);

/* Preforms the function 'func' on each map in oBoard. */
void ChessBoard_onEachMap(ChessBoard_T oBoard, MapFunction func, int *data);

/* Tries to perform oMove on oBoard. Returns SUCCESS if move could be 
   completed, some other move result otherwise and leaves the chessboard 
   untouched. */
r_move ChessBoard_tryMove(ChessBoard_T oBoard, Move_T oMove);

/* Return info about the piece currently on square oSqr. */
p_type ChessBoard_typeOnSqr(ChessBoard_T oBoard, Square_T oSqr);
p_color ChessBoard_colorOnSqr(ChessBoard_T oBoard, Square_T oSqr);

/*--------------------------------------------------------------------*/

/* Return the string representation of oBoard. CALLER FREE. */
char *ChessBoard_toString(ChessBoard_T oBoard);

#endif

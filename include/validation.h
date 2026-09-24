/*--------------------------------------------------------------------*/
/* validation.h                                                       */
/*--------------------------------------------------------------------*/

#include "board.h"

#ifndef VALIDATION_INCLUDED
#define VALIDATION_INCLUDED

/* raises an error if the chessboard is invalid */
void Validate_chessboard(ChessBoard_T oBoard);

/* return true if the destination square is a valid chess square, 
    false otherwise */
bool Validate_src_dyx (Square_T src, int dy, int dx);

/* retruns true if src and dst from move are not equal */
bool Validate_move (Move_T move);

#endif
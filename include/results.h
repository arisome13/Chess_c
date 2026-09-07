/*--------------------------------------------------------------------*/
/* results.h                                                           */
/*--------------------------------------------------------------------*/

#ifndef RESULTS_INCLUDED
#define RESULTS_INCLUDED

/* describes the end result of an attempted move */
typedef enum r_move {
    SUCCESS, DOESNT_HAVE_RANGE, SAME_COLOR_DST, 
    BLOCKED_PATH, FAIL
} r_move;

/* describes the end result of a chess game */
typedef enum r_game {
    CHECKMATE, DRAW, BORING_MOVE_50, 
    THREEFOLD_REP, STALEMATE
} r_game;

#endif
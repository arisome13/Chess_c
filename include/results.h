/*--------------------------------------------------------------------*/
/* results.h                                                           */
/*--------------------------------------------------------------------*/

#ifndef RESULTS_INCLUDED
#define RESULTS_INCLUDED

typedef enum r_move {
    SUCCESS, FAIL
} r_move;

typedef enum r_game {
    CHECKMATE, DRAW, BORING_MOVE_50, 
    THREEFOLD_REP, STALEMATE
} r_game;

#endif
/*--------------------------------------------------------------------*/
/* states.h                                                          */
/*--------------------------------------------------------------------*/

#ifndef STATES_H
#define STATES_H

/* describes the end result of an attempted move */
typedef enum s_move {
    // succeeded in moving
    SUCCESS, 
    // did not succeed in moving
    WRONG_COLOR, NO_PIECE_ON_SRC, DOESNT_HAVE_RANGE, 
    BLOCKED_PATH, SAME_COLOR_DST, GAME_HAS_ENDED, FAIL
} s_move;

/* describes the end result of a chess game */
typedef enum s_game {
    // still playing
    IN_PROGRESS, 
    // ended with a winner
    CHECKMATE, 
    // ended with a draw
    DRAW, BORING_MOVE_50, 
    THREEFOLD_REP, STALEMATE, 
    INSUFFICIENT_MATERIAL
} s_game;

char *MoveState_toString(s_move r);
char *GameState_toString(s_game r);

#endif
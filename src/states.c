/*--------------------------------------------------------------------*/
/* states.c                                                          */
/*--------------------------------------------------------------------*/

#include "states.h"

const char *MoveState_toString(s_move r)
{
    switch (r)
    {
    case SUCCESS:
        return "SUCCESS";
    case WRONG_COLOR:
        return "WRONG_COLOR";
    case NO_PIECE_ON_SRC:
        return "NO_PIECE_ON_SRC";
    case DOESNT_HAVE_RANGE:
        return "DOESNT_HAVE_RANGE";
    case BLOCKED_PATH:
        return "BLOCKED_PATH";
    case SAME_COLOR_DST:
        return "SAME_COLOR_DST";
    case GAME_HAS_ENDED:
        return "GAME_HAS_ENDED";
    case INVALID_ENP_CASE:
        return "INVALID_ENP_CASE";
    case INVALID_CASTLE_CASE:
        return "INVALID_CASTLE_CASE";
    case FAIL:
        return "FAIL";
    default:
        return "NULL MOVE RESULT";
    }
}
const char *GameState_toString(s_game r)
{
    switch (r)
    {
    case IN_PROGRESS:
        return "IN_PROGRESS";
    case CHECKMATE_WHITE:
        return "CHECKMATE_WHITE";
    case CHECKMATE_BLACK:
        return "CHECKMATE_BLACK";
    case DRAW:
        return "DRAW";
    case BORING_MOVE_50:
        return "BORING_MOVE_50";
    case THREEFOLD_REP:
        return "THREEFOLD_REP";
    case STALEMATE:
        return "STALEMATE";
    default:
        return "NULL GAME RESULT";
    }
}


/*--------------------------------------------------------------------*/
/* results.c                                                          */
/*--------------------------------------------------------------------*/

#include "results.h"

char *MoveResult_toString(r_move r)
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
    case FAIL:
        return "FAIL";
    default:
        return "NULL MOVE RESULT";
    }
}

char *GameResult_toString(r_game r)
{
    switch (r)
    {
    case CHECKMATE:
        return "CHECKMATE";
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
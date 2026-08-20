/*--------------------------------------------------------------------*/
/* engine.c                                                           */
/*--------------------------------------------------------------------*/

#include "engine.h"
#include <assert.h>

struct Engine
{
    /* A chess board object holding the pieces on the board. */
    ChessBoard_T oBoard;
   
    /* A chess parameters object holding the state of the chess game. */
    ChessParameters_T oParams;

    /* search depth: alter when testing */
    int iDepth;
};

const char *STARTING_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

Engine_T Engine_new(const char *pcFen) 
{
    Engine_T oEngine;

    oEngine = (Engine_T)calloc(1, sizeof(struct Engine));
    MEM_CHECK(oEngine);

    if (pcFen == NULL)
        pcFen = STARTING_FEN;

    oEngine->oBoard = ChessBoard_new(pcFen);
    MEM_CHECK(oEngine->oBoard);
    oEngine->oParams = ChessParameters_new(pcFen);
    MEM_CHECK(oEngine->oParams);
    
    oEngine->iDepth = 3;

    return oEngine;
}

void Engine_free(Engine_T oEngine) 
{
    assert(oEngine != NULL);

    free(oEngine->oBoard);
    free(oEngine->oParams);
    free(oEngine);
}

Engine_T Engine_copy (Engine_T oEngine)
{
    assert(oEngine);
    Engine_T oeCopy;

    oeCopy = (Engine_T)calloc(1, sizeof(struct Engine));
    MEM_CHECK(oeCopy);
    oeCopy->oBoard = ChessBoard_copy(oEngine->oBoard);
    MEM_CHECK(oeCopy->oBoard);
    oeCopy->oParams = ChessParameters_copy(oEngine->oParams);
    MEM_CHECK(oeCopy->oParams);

    oeCopy->iDepth = oEngine->iDepth;

    return oeCopy;
}

/*--------------------------------------------------------------------*/

/* Search 3 moves in to the move tree and return the best move for the 
   current player, or NULL if insufficient memory is available. 
   The parameter oEngine should be a */
Move_T Engine_search (Engine_T oEngine)
{
    /* INCOMPLETE */
    assert(oEngine != NULL);
    return Move_new(Square_newNotation("e2"), Square_newNotation("e4"));
}

void Mask_addUpPieces (Mask_T oMask, int *total) {
    assert(oMask != NULL);
    assert(total != NULL);
    *total += Type_getValue(Mask_getName(oMask)) * Mask_numPieces(oMask);
}
/* Return a score for the position held by oEngine. + if it is in 
    favor of white, - if it is in favor of black. */
int Engine_evaluate (Engine_T oEngine)
{
    assert(oEngine != NULL);
    int score = 0;

    ChessBoard_onEachMask(oEngine->oBoard, Mask_addUpPieces, &score);
    
    return score;
}


/*--------------------------------------------------------------------*/

Move_T Engine_bestMove (Engine_T oEngine)
{
    Engine_T oeCopy = Engine_copy(oEngine);

    Move_T omBest = Engine_search(oEngine);

    free(oeCopy);
    return omBest;
}

/*--------------------------------------------------------------------*/

char *Engine_toString (Engine_T oEngine)
{
    assert(oEngine != NULL);

    char *pcStrRep = malloc(900);
    char *ptr = pcStrRep;
    ptr[0] = '\0';

    char *board = ChessBoard_toString(oEngine->oBoard);
    ptr += sprintf(ptr, "%s", board);

    ptr += sprintf(ptr, "\n");

    char *params = ChessParameters_toString(oEngine->oParams);
    ptr += sprintf(ptr, "%s", params);

    ptr += sprintf(ptr, "\n");

    ptr += sprintf(ptr, "  Engine eval: %d", Engine_evaluate(oEngine));

    ptr += sprintf(ptr, "\n");

    return pcStrRep;
}

/*--------------------------------------------------------------------*/
/* engine.c                                                           */
/*--------------------------------------------------------------------*/

#include "engine.h"
#include "results.h"
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

/* Return a score for the position held by oEngine. + if it is in 
    favor of white, - if it is in favor of black. */
int Engine_evaluate (Engine_T oEngine)
{
    assert(oEngine != NULL);
    int score = 0;

    // comparing material
    ChessBoard_onEachMap(oEngine->oBoard, Map_addUpPieces, &score);
    
    return score;
}

/* Search 3 moves in to the move tree and return the best move for the 
   current player, or NULL if insufficient memory is available. */
Move_T Engine_search (Engine_T oEngine)
{
    assert(oEngine != NULL);

    if (oEngine->iDepth == 0)
    {
        
    }
    return Move_new(Square_newNotation("e2"), Square_newNotation("b4"));
}

Move_T Engine_bestMove (Engine_T oEngine)
{
    Engine_T oeCopy = Engine_copy(oEngine);

    Move_T omBest = Engine_search(oeCopy);

    free(oeCopy);
    return omBest;
}

/*--------------------------------------------------------------------*/

void Engine_makeMove (Engine_T oEngine, Move_T oMove)
{
    MEM_CHECK(oEngine);
    MEM_CHECK(oMove);

    r_move result = ChessBoard_tryMove(oEngine->oBoard, oMove);
    switch (result)
    {
        case SUCCESS:
            return;
        case FAIL:
            ERROR("Invalid move: %s\n", Move_toString(oMove));
            return;
        default:
            ERROR("r_move result is not recognized: %d", result);
            return;
    }
}

/*--------------------------------------------------------------------*/

char *Engine_toString (Engine_T oEngine)
{
    assert(oEngine != NULL);

    char *pcStrRep = malloc(900);
    char *ptr = pcStrRep;
    ptr[0] = '\0';

    char *board = ChessBoard_toString(oEngine->oBoard);
    ptr += sprintf(ptr, "%s\n\n", board);

    char *params = ChessParameters_toString(oEngine->oParams);
    ptr += sprintf(ptr, "%s\n\n", params);

    ptr += sprintf(ptr, "  Engine eval: %d", Engine_evaluate(oEngine));

    return pcStrRep;
}

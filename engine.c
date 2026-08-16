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

    /* search depth */
    int iDepth;
};


Engine_T Engine_new(const char *pcFen) {
    Engine_T oEngine;

    assert(pcFen != NULL);

    oEngine = (Engine_T)calloc(1, sizeof(struct Engine));
    if (oEngine == NULL)
        return NULL;
    
    oEngine->oBoard = ChessBoard_new(pcFen);
    if (oEngine->oBoard == NULL)
        return NULL;

    oEngine->oParams = ChessParameters_new(pcFen);
    if (oEngine->oParams == NULL)
        return NULL;
    
    /* alter when testing */
    oEngine->iDepth = 3;

    return oEngine;
}

void Engine_free(Engine_T oEngine) {
    assert(oEngine != NULL);

    free(oEngine->oBoard);
    free(oEngine->oParams);
    free(oEngine);
}

/*--------------------------------------------------------------------*/

/* unfinished */
Move_T Engine_bestMove (Engine_T oEngine) {
    return Move_new(Square_newNotation("a2"), Square_newNotation("a4"));
}

/*--------------------------------------------------------------------*/

/* unfinished */
char *Engine_toString (Engine_T oEngine) {
    char *pcStrRep = malloc(300);

    assert(oEngine != NULL);

    pcStrRep[0] = '\0';
    return pcStrRep;
}

/*--------------------------------------------------------------------*/
/* engine.c                                                           */
/*--------------------------------------------------------------------*/

#include "engine.h"
#include "board.h"
#include "parameters.h"
#include "eval.h"

const char *STARTING_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
enum {MAX_DEPTH = 8};

struct Engine
{
    /* A chess board object holding the pieces on the board. */
    ChessBoard_T oBoard;
   
    /* A chess parameters object holding the state of the chess game. */
    ChessParameters_T oParams;

    /* search depth: alter when testing. 0 < iDepth <= 8 */
    size_t iDepth;
};

Engine_T Engine_new(const char *pcFen) 
{
    Engine_T oEngine;

    oEngine = (Engine_T)calloc(1, sizeof(struct Engine));
    CHECK_MEM(oEngine);

    if (pcFen == NULL)
        pcFen = STARTING_FEN;

    oEngine->oBoard = ChessBoard_new(pcFen);
    CHECK_MEM(oEngine->oBoard);
    oEngine->oParams = ChessParameters_new(pcFen);
    CHECK_MEM(oEngine->oParams);
    
    Engine_setDepth(oEngine, 1);

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
    CHECK_MEM(oeCopy);
    oeCopy->oBoard = ChessBoard_copy(oEngine->oBoard);
    CHECK_MEM(oeCopy->oBoard);
    oeCopy->oParams = ChessParameters_copy(oEngine->oParams);
    CHECK_MEM(oeCopy->oParams);

    oeCopy->iDepth = oEngine->iDepth;

    return oeCopy;
}

/*--------------------------------------------------------------------*/

/* Return an evaluation for the position held by oEngine. + if it is in 
    favor of white, - if it is in favor of black. CALLER FREE. */
Eval_T Engine_evaluate (Engine_T oEngine)
{
    CHECK_NULL(oEngine);

    // comparing material
    int score = 0;
    ChessBoard_onEachMap(oEngine->oBoard, Map_addUpPieces, &score);

    Eval_T eval = Eval_new(CENTIPAWN, score);
    
    return eval;
}

/* Search oEngine's position. CALLER FREE. */
Eval_T Engine_search (Engine_T oEngine)
{
    CHECK_NULL(oEngine);
    
    printf("NOT IMPLEMENTED: Engine_search");
    
    return NULL;
}

Move_T Engine_bestMove (Engine_T oEngine)
{
    CHECK_NULL(oEngine);

    // copy the current engine
    Engine_T oeCopy = Engine_copy(oEngine);
    // search the move tree for the best move
    Move_T bestMove = Move_new(Square_newNotation("b2"), Square_newNotation("c3"));
    Eval_T bestEval = NULL;
    Eval_T tempEval;
    /*
    for (piece in pieces)
        for (move in moves)
            if (move is possible)
                oeCopy = Engine_copy(oEngine)
                Engine_makeMove(move)
                tempEval = Engine_search(oeCopy)
                if (Eval_compare(tempEval, bestEval) > 0)
                    bestEval = tempEval
                    bestMove = move
    */
    
    free(oeCopy);
    //free(bestEval);
    //free(tempEval);

    // return the best move
    return bestMove;
}

/*--------------------------------------------------------------------*/

void Engine_makeMove (Engine_T oEngine, Move_T oMove)
{
    CHECK_NULL(oEngine);
    CHECK_NULL(oMove);
    char *s = Move_toString(oMove);

    // check if the turn color matches the selected piece
    if (ChessParameters_turnColor(oEngine->oParams) 
        != ChessBoard_colorOnSqr(oEngine->oBoard, Move_src(oMove)))
            ERROR("Invalid move %s, reason %d\n", s, WRONG_COLOR);

    // run chessboard to try and make the requested move
    r_move result = ChessBoard_tryMove(oEngine->oBoard, oMove);

    // raise error if the move could not be made
    if (result != SUCCESS) 
        ERROR("Invalid move %s, reason %d\n", s, result);
    
    PRINT("Succeeded in moving: %s\n", s);

    bool movedTwoSqrsForward = 
        Move_dst(oMove)->x == Move_src(oMove)->x 
        && abs(
            (int)Move_dst(oMove)->y - (int)Move_src(oMove)->x
        ) == 2;
    p_type piece = ChessBoard_typeOnSqr(oEngine->oBoard, Move_dst(oMove));
    if (movedTwoSqrsForward && piece == PAWN) 
    {
        size_t yEnpCoord = 
            (Move_dst(oMove)->y - Move_src(oMove)->y) / 2 
            + Move_src(oMove)->y;
        Square_T enp = Square_newCoords(yEnpCoord, Move_dst(oMove)->x);
        ChessParameters_setEnpSqr(oEngine->oParams, enp);
    }
    
    ChessParameters_incrementMove(oEngine->oParams, piece == PAWN);

    free(s);
}

void Engine_setDepth (Engine_T oEngine, size_t d) {
    CHECK_NULL(oEngine);
    assert(0 < d && d < MAX_DEPTH);
    oEngine->iDepth = d;
}

/*--------------------------------------------------------------------*/

char *Engine_toString (Engine_T oEngine)
{
    CHECK_NULL(oEngine);

    char *pcStrRep = malloc(900);
    CHECK_MEM(pcStrRep);
    
    char *ptr = pcStrRep;
    ptr[0] = '\0';

    char *board = ChessBoard_toString(oEngine->oBoard);
    ptr += sprintf(ptr, "%s\n\n", board);

    char *params = ChessParameters_toString(oEngine->oParams);
    ptr += sprintf(ptr, "%s\n\n", params);

    char *eval = Eval_toString(Engine_evaluate(oEngine));
    ptr += sprintf(ptr, "  Engine eval: %s", eval);

    free(board);
    free(params);
    free(eval);
    return pcStrRep;
}

/*--------------------------------------------------------------------*/
/* engine.c                                                           */
/*--------------------------------------------------------------------*/

#include "engine.h"
#include "board.h"
#include "parameters.h"
#include "movepattern.h"
#include "validation.h"

#define STARTING_FEN    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define MAX_DEPTH       8
#define MAX_MOVES       256
#define DEFAULT_DEPTH   4

struct Engine
{
    /* A chess board object holding the pieces on the board. */
    ChessBoard_T oBoard;
   
    /* A chess parameters object holding the state of the chess game. */
    ChessParameters_T oParams;

    /* Enables and disables castling. */
    bool CASTLING;

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
    
    oEngine->CASTLING = false;
    Engine_setDepth(oEngine, DEFAULT_DEPTH);

    return oEngine;
}
void Engine_free(Engine_T oEngine) 
{
    assert(oEngine != NULL);
    ChessBoard_free(oEngine->oBoard);
    ChessParameters_free(oEngine->oParams);
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

    oeCopy->CASTLING = oEngine->CASTLING;
    oeCopy->iDepth = oEngine->iDepth;

    return oeCopy;
}

/*--------------------------------------------------------------------*/

static char *Engine_getFen (Engine_T oEngine) {
    CHECK_NULL(oEngine);

    return ChessBoard_getFen(oEngine->oBoard);
}

void Engine_setDepth (Engine_T oEngine, size_t d) {
    CHECK_NULL(oEngine);
    assert(0 < d && d < MAX_DEPTH);
    oEngine->iDepth = d;
}
r_move Engine_makeMove (Engine_T oEngine, Move_T oMove)
{
    CHECK_NULL(oEngine);
    CHECK_NULL(oMove);

    // check if the turn color matches the selected piece
    if (ChessParameters_turnColor(oEngine->oParams) 
        != ChessBoard_colorOnSqr(oEngine->oBoard, Move_src(oMove)))
            return WRONG_COLOR;

    // run chessboard to try and make the requested move
    r_move result = ChessBoard_tryMove(oEngine->oBoard, oMove);

    // check for unusual moves 
    if (result != SUCCESS) {
        if (false /* is a pawn attacking */)
            ;
        if (false /* is a castle */)
            ;
    }

    // raise error if the move could not be made
    if (result != SUCCESS) 
        return result;

    p_type piece = ChessBoard_typeOnSqr(oEngine->oBoard, Move_dst(oMove));
    
    if (piece == PAWN) 
    {
        if (Move_dst(oMove)->x == Move_src(oMove)->x 
                && abs((int)Move_dst(oMove)->y 
                     - (int)Move_src(oMove)->y) == 2) {
            size_t yEnpCoord = 
                ((int)Move_dst(oMove)->y - (int)Move_src(oMove)->y) / 2 
                + Move_src(oMove)->y;
            Square_T enp = Square_newCoords(yEnpCoord, Move_dst(oMove)->x);
            ChessParameters_setEnpSqr(oEngine->oParams, enp);
        }
    }

    bool isCapture = false; // update this
    
    ChessParameters_incrementMove(oEngine->oParams, piece == PAWN || isCapture);

    return SUCCESS;
}

/*--------------------------------------------------------------------*/

size_t Engine_legalMoves (Engine_T oEngine, Move_T aMoves[])
{
    CHECK_NULL(oEngine);
    CHECK_NULL(aMoves);

    Square_T src = Square_newCoords(0, 0);
    Square_T dst = Square_newCoords(0, 0);
    Move_T move = Move_new(src, dst);
    size_t uiCount = 0;

    p_color moveColor = ChessParameters_turnColor(oEngine->oParams);
    assert(moveColor != NO_COLOR);
    
    // for every single square pair
    for (int src_y = 0; src_y < 8; src_y++) { src->y = src_y;
    for (int src_x = 0; src_x < 8; src_x++) { src->x = src_x;

        // discard source locations that don't have the correct 
        // color of piece on it
        if (moveColor != ChessBoard_colorOnSqr(oEngine->oBoard, src))
            continue;

        for (int dst_y = 0; dst_y < 8; dst_y++) { dst->y = dst_y; 
        for (int dst_x = 0; dst_x < 8; dst_x++) { dst->x = dst_x;
            Engine_T oeCopy = Engine_copy(oEngine);

            // check if the move is valid and add to the move list
            r_move result = Engine_makeMove(oeCopy, move);
            if (result == SUCCESS)
                aMoves[uiCount++] = Move_copy(move);

            // reset engine set up
            Engine_free(oeCopy);

            // break out if 
            if (uiCount >= MAX_MOVES)
                goto got_max_moves;
        }}
    }} got_max_moves:

    Move_free(move);
    return uiCount;
}

/* Return a score for the position held by oEngine. + if it is in 
    favor of white, - if it is in favor of black. CALLER FREE. */
static Eval_T Engine_score (Engine_T oEngine)
{
    CHECK_NULL(oEngine);

    // comparing material
    int score = 0;
    ChessBoard_onEachMap(oEngine->oBoard, Map_addUpPieces, &score);

    Eval_T eval = Eval_new(CENTIPAWN, score);
    
    return eval;
}

/* Returns the evaluation of the position. */
static Eval_T Engine_search (Engine_T oEngine, size_t depth, 
        Eval_T bestWhite, Eval_T bestBlack, Move_T outputBestMove)
{
    CHECK_NULL(oEngine);

    if (oEngine->iDepth < depth)
        ERROR("Engine depth %zu > search depth %zu\n", oEngine->iDepth, depth);

    size_t search_depth = oEngine->iDepth - depth;

    // base case
    if (depth-- == 0) {
        Eval_T score = Engine_score(oEngine);
        
        if (DEBUG) {
            char *evalStr = Eval_toString(score);
            PRINT_I(search_depth, "Got base case: returning (%s)\n", evalStr);
            free(evalStr);
        }
        
        return score;
    } // else, search the move tree one level lower

    Eval_T bestEval = NULL;
    size_t bestIndex = 0;
    Move_T legalMoves[MAX_MOVES];
    r_move result;

    // preemptively get this move's color
    p_color moveColor = ChessParameters_turnColor(oEngine->oParams);
    // get all the legal moves from this position
    size_t moveListSize = Engine_legalMoves(oEngine, legalMoves);

    // if there are no legal moves, return a forced mate (update this for later)
    if (moveListSize == 0) {
        // if (in check) {
            int value = search_depth;
            if (moveColor == WHITE) 
                value = -value;
            return Eval_new(FORCED_MATE, value); // checkmate
        //} else 
            // return Eval_new(CENTIPAWN, 0); // stalemate
    }

    // cycle through each move, checking for a better eval
    for (size_t i = 0; i < moveListSize; i++) {
        Engine_T oeCopy = Engine_copy(oEngine);
        result = Engine_makeMove(oeCopy, legalMoves[i]);
        assert(result == SUCCESS);
        (void)result; // silences a compiler warning about an unused var

        if (DEBUG) {
            char *pcMoveStr = ChessBoard_notation(oEngine->oBoard, legalMoves[i]);
            PRINT_I(search_depth, "Made move: %s\n", pcMoveStr);
            free(pcMoveStr);
        }

        // recurse to find the evaluation for this move sequence
        Eval_T tempEval = Engine_search(oeCopy, depth, bestWhite, bestBlack, NULL);
        Engine_free(oeCopy);

        if (bestEval == NULL
            || (moveColor == WHITE && Eval_compare(tempEval, bestEval) > 0)
            || (moveColor == BLACK && Eval_compare(tempEval, bestEval) < 0)) {
            
            Eval_T oldBest = bestEval;
            bestEval = tempEval;
            bestIndex = i;
            
            // alter bestWhite bestBlack
            if (moveColor == WHITE) {
                if (bestWhite == NULL || Eval_compare(bestEval, bestWhite) > 0)
                    bestWhite = bestEval;
            } else {
                if (bestBlack == NULL || Eval_compare(bestEval, bestBlack) < 0)
                    bestBlack = bestEval;
            }

            if (oldBest != NULL)
                Eval_free(oldBest);
        } else {
            Eval_free(tempEval);
        }

        if (bestWhite != NULL && bestBlack != NULL && Eval_compare(bestWhite, bestBlack) >= 0)
            break;
    }

    if (DEBUG) {
        CHECK_NULL(legalMoves[bestIndex]);
        char *movestr = Move_toString(legalMoves[bestIndex]);
        CHECK_NULL(bestEval);
        char *evalstr = Eval_toString(bestEval);
        PRINT_I(search_depth, "Bests: (%s) with %s\n", movestr, evalstr);
        free(movestr);
        free(evalstr);
    }

    // return the best move
    if (outputBestMove != NULL)
        Move_copyTo(legalMoves[bestIndex], outputBestMove);
    
    // free the used pointers
    for (size_t i = 0; i < moveListSize; i++) 
        Move_free(legalMoves[i]);

    // return the maximum possible evaluation
    return bestEval;
}

Eval_T Engine_evaluate (Engine_T oEngine)
{
    PRINT("evaluating...\n");
    CHECK_NULL(oEngine);
    return Engine_search(oEngine, oEngine->iDepth, NULL, NULL, NULL);
}
Move_T Engine_bestMove (Engine_T oEngine)
{
    PRINT("Checking for best move.\n");
    CHECK_NULL(oEngine);
    
    Move_T bestMove = Move_new(Square_newCoords(0, 0), Square_newCoords(0, 0));
    Eval_T eval = Engine_search(oEngine, oEngine->iDepth, NULL, NULL, bestMove);
    
    char *moveStr = Move_toString(bestMove);
    PRINT("Best move is: %s\n", moveStr);
    free(moveStr);
    Eval_free(eval);
    
    if (!Validate_move(bestMove))
    {
        Move_free(bestMove);
        return NULL;
    }
    return bestMove;
}

/*--------------------------------------------------------------------*/

char *Engine_notation (Engine_T oEngine, Move_T oMove) {
    return ChessBoard_notation(oEngine->oBoard, oMove);
}
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

    free(board);
    free(params);
    return pcStrRep;
}

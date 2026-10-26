/*--------------------------------------------------------------------*/
/* engine.c                                                           */
/*--------------------------------------------------------------------*/

#include "engine.h"
#include "board.h"
#include "parameters.h"
#include "movepattern.h"
#include "validation.h"
#include "undoinfo.h"
#include "movearray.h"

struct Engine
{
    /* A chess board object holding the pieces on the board. */
    ChessBoard_T oBoard;
   
    /* A chess parameters object holding the state of the chess game. */
    ChessParameters_T oParams;

    /* An undo move object holding the informaiton to undo 
        the previous moves played. */
    UndoInfo_T oUndoList;

    /* Enables and disables castling. */
    bool CASTLING;

    /* search depth: alter when testing. 0 < iDepth <= 8 */
    size_t iDepth;

    /* represents the current state of this engine's chess game */
    s_game rGameState;
};

enum {DEFAULT_DEPTH = 4, MAX_DEPTH = 8};

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
    
    oEngine->oUndoList = NULL;
    oEngine->CASTLING = false;
    Engine_setDepth(oEngine, DEFAULT_DEPTH);
    oEngine->rGameState = IN_PROGRESS;

    return oEngine;
}
void Engine_free(Engine_T oEngine) 
{
    CHECK_NULL(oEngine);

    ChessBoard_free(oEngine->oBoard);
    ChessParameters_free(oEngine->oParams);
    if (oEngine->oUndoList != NULL)
        UndoInfo_free(oEngine->oUndoList);
    
    free(oEngine);
}
Engine_T Engine_copy (Engine_T oEngine)
{
    CHECK_NULL(oEngine);
    
    Engine_T oeCopy = (Engine_T)calloc(1, sizeof(struct Engine));
    CHECK_MEM(oeCopy);

    oeCopy->oBoard = ChessBoard_copy(oEngine->oBoard);
    oeCopy->oParams = ChessParameters_copy(oEngine->oParams);
    oeCopy->oUndoList = (oEngine->oUndoList == NULL) ? NULL : UndoInfo_copy(oEngine->oUndoList);

    oeCopy->CASTLING = oEngine->CASTLING;
    oeCopy->iDepth = oEngine->iDepth;
    oeCopy->rGameState = oEngine->rGameState;

    return oeCopy;
}

/*--------------------------------------------------------------------*/

/* Return the engine's fen representation. Currently implemented to 
    just showing the char board (not the parameters). */
static char *Engine_getFen (Engine_T oEngine) {
    CHECK_NULL(oEngine);
    return ChessBoard_getFen(oEngine->oBoard);
}
/* Update the engine's game state (checkmate, draw, etc.) */
static void Engine_updateGameState (Engine_T oEngine)
{
    // default value
    oEngine->rGameState = IN_PROGRESS;

    // check for checkmate
    if (ChessBoard_numPieces(oEngine->oBoard, KING, WHITE) > 0) {
        if (ChessBoard_numPieces(oEngine->oBoard, KING, BLACK) > 0) {
            // nothing
        } else {
            oEngine->rGameState = CHECKMATE_WHITE;
            return;
        }
    } else {
        if (ChessBoard_numPieces(oEngine->oBoard, KING, BLACK) > 0) {
            oEngine->rGameState = CHECKMATE_BLACK;
            return;
        } else {
            ERROR("Both white and black king are not present on the board.");
        }
    }

    if (ChessParameters_50MoveRule(oEngine->oParams) >= 50) {
        oEngine->rGameState = BORING_MOVE_50;
    } else if (!ChessBoard_sufficientMaterial(oEngine->oBoard)) {
        oEngine->rGameState = INSUFFICIENT_MATERIAL;
    } else {
        UndoInfo_T ui1 = UndoInfo_getNextUndo(oEngine->oUndoList);
        if (ui1 == NULL) goto isnt3fold;
        UndoInfo_T ui2 = UndoInfo_getNextUndo(ui1);
        if (ui2 == NULL) goto isnt3fold;
        UndoInfo_T ui3 = UndoInfo_getNextUndo(ui2);
        if (ui3 == NULL) goto isnt3fold;
        UndoInfo_T ui4 = UndoInfo_getNextUndo(ui3);
        if (ui4 == NULL) goto isnt3fold;
        UndoInfo_T ui5 = UndoInfo_getNextUndo(ui4);
        if (ui5 == NULL) goto isnt3fold;
        UndoInfo_T ui6 = UndoInfo_getNextUndo(ui5);
        if (ui6 == NULL) goto isnt3fold;
        UndoInfo_T ui7 = UndoInfo_getNextUndo(ui6);
        if (ui7 == NULL) goto isnt3fold;

        Move_T m0 = UndoInfo_getMove(oEngine->oUndoList);
        DEBUG_ASSERT(m0 != NULL, "invalid undo, move is null\n");
        Square_T src0 = Move_src(m0); Square_T dst0 = Move_dst(m0);
        Move_T m1 = UndoInfo_getMove(ui1);
        DEBUG_ASSERT(m1 != NULL, "invalid undo, move is null\n");
        Square_T src1 = Move_src(m1); Square_T dst1 = Move_dst(m1);

        // opposite of first moves
        Move_T m2 = UndoInfo_getMove(ui2);
        DEBUG_ASSERT(m2 != NULL, "invalid undo, move is null\n");
        if (!(Square_equals(Move_src(m2), dst0) 
                && Square_equals(Move_dst(m2), src0)))
            goto isnt3fold;
        Move_T m3 = UndoInfo_getMove(ui3);
        DEBUG_ASSERT(m3 != NULL, "invalid undo, move is null\n");
        if (!(Square_equals(Move_src(m3), dst1) 
                && Square_equals(Move_dst(m3), src1)))
            goto isnt3fold;
        
        // same as first moves
        Move_T m4 = UndoInfo_getMove(ui4);
        DEBUG_ASSERT(m4 != NULL, "invalid undo, move is null\n");
        if (!(Square_equals(Move_src(m4), src0) 
                && Square_equals(Move_dst(m4), dst0)))
            goto isnt3fold;
        Move_T m5 = UndoInfo_getMove(ui5);
        DEBUG_ASSERT(m5 != NULL, "invalid undo, move is null\n");
        if (!(Square_equals(Move_src(m5), src1) 
                && Square_equals(Move_dst(m5), dst1)))
            goto isnt3fold;
        
        // same as second moves
        Move_T m6 = UndoInfo_getMove(ui6);
        DEBUG_ASSERT(m6 != NULL, "invalid undo, move is null\n");
        if (!(Square_equals(Move_src(m6), dst0) 
                && Square_equals(Move_dst(m6), src0)))
            goto isnt3fold;
        Move_T m7 = UndoInfo_getMove(ui7);
        DEBUG_ASSERT(m7 != NULL, "invalid undo, move is null\n");
        if (!(Square_equals(Move_src(m7), dst1) 
                && Square_equals(Move_dst(m7), src1)))
            goto isnt3fold;

        oEngine->rGameState = THREEFOLD_REP;
        
        isnt3fold:
    }
}
/* SOMETHING */
static void Engine_undo (Engine_T oEngine)
{
    CHECK_NULL(oEngine);

    UndoInfo_T toUndo = oEngine->oUndoList;
    oEngine->oUndoList = UndoInfo_getNextUndo(toUndo);
    oEngine->rGameState = IN_PROGRESS;

    DEBUG_ASSERT(ChessParameters_undo(oEngine->oParams, toUndo), 
        "ChessParameters_undo must succeed.");
    DEBUG_ASSERT(ChessBoard_undo(oEngine->oBoard, toUndo), 
        "ChessBoard_undo must succeed.");

    char *movestr = Move_toString(UndoInfo_getMove(toUndo));
    //PRINT("Engine undid: %s.\n", movestr);
    free(movestr);

    UndoInfo_free(toUndo);
}

/*--------------------------------------------------------------------*/

void Engine_setDepth (Engine_T oEngine, size_t d) {
    CHECK_NULL(oEngine);
    assert(0 < d && d < MAX_DEPTH);
    oEngine->iDepth = d;
}
s_move Engine_makeMove (Engine_T oEngine, Move_T oMove)
{
    CHECK_NULL(oEngine);
    CHECK_NULL(oMove);

    if (oEngine->rGameState != IN_PROGRESS)
        return GAME_HAS_ENDED;

    // check if the turn color matches the selected piece
    Square_T srcSqr = Move_src(oMove);
    p_color turnColor = ChessParameters_turnColor(oEngine->oParams);
    p_color srcColor = ChessBoard_colorOnSqr(oEngine->oBoard, srcSqr);
    if (turnColor != srcColor)
        return WRONG_COLOR;

    // initialize the new undo info object
    UndoInfo_T newUndo = UndoInfo_new(
        oMove, 
        ChessParameters_castles(oEngine->oParams), 
        ChessParameters_enpSqr(oEngine->oParams),
        ChessParameters_50MoveRule(oEngine->oParams),
        oEngine->oUndoList
    );
    
    // check for capture
    Square_T dstSqr = Move_dst(oMove);
    p_color dstColor = ChessBoard_colorOnSqr(oEngine->oBoard, dstSqr);
    bool isCapture = false;
    if (dstColor != NO_COLOR && dstColor != turnColor) {
        isCapture = true;
        UndoInfo_logCapture(newUndo, 
            dstSqr, ChessBoard_typeOnSqr(
                oEngine->oBoard, dstSqr
            ), dstColor);
    }

    // get the type of the moving piece
    p_type pieceType = ChessBoard_typeOnSqr(oEngine->oBoard, srcSqr);

    // run chessboard to try and make the requested move
    char *movestr = ChessBoard_notation(oEngine->oBoard, oMove);
    s_move result = ChessBoard_tryMove(oEngine->oBoard, oMove);
    
    // check for unusual moves 
    int yMovement = (int)dstSqr->y - (int)srcSqr->y;
    int xMovement = (int)dstSqr->x - (int)srcSqr->x;
    s_move altResult = FAIL;
    if (result != SUCCESS) { switch (pieceType)
    {
        case PAWN:
            if (ChessParameters_enpSqr(oEngine->oParams) != NULL 
                    && Square_equals(dstSqr, ChessParameters_enpSqr(oEngine->oParams))
                    && abs(yMovement) == 1 && abs(xMovement) == 1) 
            {
                altResult = ChessBoard_tryEnpassant(oEngine->oBoard, oMove);
                if (altResult != SUCCESS)
                    break;
                
                isCapture = true;
                Square_T enpPawnSqr = Square_copy(srcSqr);
                enpPawnSqr->x += xMovement;
                UndoInfo_logCapture(newUndo, enpPawnSqr, PAWN, 
                    Color_oposite(srcColor));
                Square_free(enpPawnSqr);
            }
            break;

        case KING:
            if (abs(xMovement) == 2 && yMovement == 0)
            {
                altResult = ChessBoard_tryCastle(oEngine->oBoard, oMove);
                if (altResult != SUCCESS)
                    break;

                if (turnColor == WHITE) {// white castle
                    ChessParameters_removeCastle(oEngine->oParams, 'K');
                    ChessParameters_removeCastle(oEngine->oParams, 'Q');
                } else { // black castle
                    ChessParameters_removeCastle(oEngine->oParams, 'k');
                    ChessParameters_removeCastle(oEngine->oParams, 'q');
                }

                UndoInfo_logCastle(newUndo);
            }
            break;

        default:
            break;
    }}

    // raise error if the move could not be made
    if (result != SUCCESS && altResult != SUCCESS) 
    {
        UndoInfo_free(newUndo);
        return result;
    }

    ChessParameters_incrementMove(oEngine->oParams, pieceType == PAWN || isCapture);

    if (pieceType == PAWN && xMovement == 0 && abs(yMovement) == 2)
    {
        size_t yEnpCoord = yMovement / 2 + srcSqr->y;
        DEBUG_ASSERT(0 <= yEnpCoord && yEnpCoord <= 7, 
            "Invalid enp coord. Overflow error likely.\n");

        Square_T enp = Square_newCoords(yEnpCoord, dstSqr->x);
        ChessParameters_setEnpSqr(oEngine->oParams, enp);
        
        UndoInfo_logEnpassant(newUndo);
    }

    if (pieceType == PAWN
            && ((dstSqr->y == 7 && srcColor == BLACK)
            || (dstSqr->y == 0 && srcColor == WHITE))) {
        UndoInfo_logPromotion(newUndo, PAWN);
        ChessBoard_promote(oEngine->oBoard, dstSqr, QUEEN);
    }

    if (pieceType == KING) 
    {
        if (srcColor == WHITE) {
            ChessParameters_removeCastle(oEngine->oParams, 'K');
            ChessParameters_removeCastle(oEngine->oParams, 'Q');
        } else {
            ChessParameters_removeCastle(oEngine->oParams, 'k');
            ChessParameters_removeCastle(oEngine->oParams, 'q');
        }
    }
    else if (pieceType == ROOK)
    {
        if (srcColor == WHITE && srcSqr->y == 7)
        {
            if (srcSqr->x == 0)
                ChessParameters_removeCastle(oEngine->oParams, 'Q');
            else if (srcSqr->x == 7)
                ChessParameters_removeCastle(oEngine->oParams, 'K');
        }
        else if (srcColor == BLACK && srcSqr->y == 0)
        {
            if (srcSqr->x == 0)
                ChessParameters_removeCastle(oEngine->oParams, 'q');
            else if (srcSqr->x == 7)
                ChessParameters_removeCastle(oEngine->oParams, 'k');
        }
    }

    free(movestr);
    oEngine->oUndoList = newUndo;
    Engine_updateGameState(oEngine);
    return SUCCESS;
}
MoveArray_T Engine_legalMoves (Engine_T oEngine)
{
    CHECK_NULL(oEngine);
    DEBUG_ASSERT(oEngine->rGameState == IN_PROGRESS, 
        "Can't evaluate the legal moves, the game isn't in progress.");

    Square_T src = Square_newCoords(0, 0);
    Square_T dst = Square_newCoords(0, 0);
    Move_T move = Move_new(src, dst);

    p_color moveColor = ChessParameters_turnColor(oEngine->oParams);
    assert(moveColor != NO_COLOR);

    MoveArray_T aMoves = MoveArray_new();
    
    // for every single square pair
    for (int src_y = 0; src_y < 8; src_y++) { src->y = src_y;
    for (int src_x = 0; src_x < 8; src_x++) { src->x = src_x;

        // discard source locations that don't have the correct 
        // color of piece on it
        if (moveColor != ChessBoard_colorOnSqr(oEngine->oBoard, src))
            continue;

        for (int dst_y = 0; dst_y < 8; dst_y++) { dst->y = dst_y; 
        for (int dst_x = 0; dst_x < 8; dst_x++) { dst->x = dst_x;
            // check if the move is valid and add to the move list
            s_move result = Engine_makeMove(oEngine, move);
            
            // if the engine succeeded in moving, 
            // add the move and reset the engine
            if (result == SUCCESS)
            {
                MoveArray_add(aMoves, move);
                Engine_undo(oEngine);
            }
        }}
    }}

    if (MoveArray_length(aMoves) == 0)
        oEngine->rGameState = STALEMATE;

    Move_free(move); // frees dst and src as well
    return aMoves;
}

/*--------------------------------------------------------------------*/

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
    size_t search_depth = oEngine->iDepth - depth;

    // return if in base case
    if (depth-- == 0)
        return Engine_score(oEngine);

    // else: search the move tree one level lower

    Eval_T bestEval = NULL;
    size_t bestIndex = 0;
    s_move result;

    // preemptively get this move's color
    p_color moveColor = ChessParameters_turnColor(oEngine->oParams);

    // if the game isn't in progress, return the end result
    switch (oEngine->rGameState)
    {
        case CHECKMATE_BLACK:
            return Eval_new(FORCED_MATE, -search_depth);
        case CHECKMATE_WHITE:
            return Eval_new(FORCED_MATE, search_depth);
        case DRAW:
        case BORING_MOVE_50:
        case THREEFOLD_REP:
        case STALEMATE:
        case INSUFFICIENT_MATERIAL:
            return Eval_new(CENTIPAWN, 0);
        case IN_PROGRESS:
            break;
    }

    // get all the legal moves from this position
    MoveArray_T legalMoves = Engine_legalMoves(oEngine);
    if (oEngine->rGameState == STALEMATE)
        return Eval_new(CENTIPAWN, 0);

    // cycle through each move, checking for a better eval
    for (size_t i = 0; i < MoveArray_length(legalMoves); i++) 
    {
        Move_T move = MoveArray_get(legalMoves, i);
        result = Engine_makeMove(oEngine, move);

        DEBUG_ASSERT(result == SUCCESS,
            "already checked by legalMoves, has to be legal");
        (void)result; // silences the unused var compiler warning

        // recurse to find the evaluation for this move sequence
        Eval_T tempEval = Engine_search(oEngine, depth, bestWhite, bestBlack, NULL);
        Engine_undo(oEngine);

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

    Move_T bestMove = MoveArray_get(legalMoves, bestIndex);
    if (DEBUG) // print the best move and eval
    {
        CHECK_NULL(bestEval);
        
        char *movestr = Move_toString(bestMove);
        char *evalstr = Eval_toString(bestEval);
        
        //DEBUG_PRINT(search_depth, "Bests: (%s) with %s\n", movestr, evalstr);
        
        free(movestr);
        free(evalstr);
    }

    // return the best move
    if (outputBestMove != NULL)
        Move_copyTo(bestMove, outputBestMove);
    
    // free the move list
    MoveArray_free(legalMoves);
    // return the maximum possible evaluation
    return bestEval;
}

Eval_T Engine_evaluate (Engine_T oEngine)
{
    CHECK_NULL(oEngine);
    return Engine_search(oEngine, oEngine->iDepth, NULL, NULL, NULL);
}
Move_T Engine_bestMove (Engine_T oEngine)
{
    CHECK_NULL(oEngine);
    
    Move_T bestMove = Move_read("b1a3");
    Eval_T eval = Engine_search(oEngine, oEngine->iDepth, NULL, NULL, bestMove);
    
    if (!Validate_move(bestMove))
    {
        if (bestMove != NULL)
            Move_free(bestMove);
        if (eval != NULL)
            Eval_free(eval);
        return NULL;
    }
    
    Eval_free(eval);
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
    ptr += snprintf(ptr, 803, "%s\n\n", board);

    char *params = ChessParameters_toString(oEngine->oParams);
    ptr += snprintf(ptr, 803, "%s\n\n", params);

    free(board);
    free(params);
    return pcStrRep;
}
BoardInfo_T Engine_getInfo (Engine_T oEngine) {
    return ChessBoard_getInfo(oEngine->oBoard);
}
void Engine_PRINT(Engine_T oEngine)
{
    char *tempStr = Engine_toString(oEngine);
    printf("%s\n", tempStr);
    free(tempStr);
}

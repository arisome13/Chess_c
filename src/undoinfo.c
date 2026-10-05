/*--------------------------------------------------------------------*/
/* undoinfo.c                                                         */
/*--------------------------------------------------------------------*/

#include "undoinfo.h"

struct UndoInfo 
{
    Move_T      move;
    Castles_T   prevCastlingRights;
    Square_T    prevEnpSquare;
    size_t      prevHalfmoveClock;
    UndoInfo_T  prevUndo;

    // captures
    bool        wasCapture;
    p_color     capturedPieceColor;
    p_type      capturedPieceType;
    Square_T    capturedSquare;

    // enpassant
    bool        wasEnpMove;

    // castle
    bool        wasCastle;

    // promotion
    bool        wasPromotion;
    p_type      promotedFromType;
};

UndoInfo_T UndoInfo_new (Move_T oMove, Castles_T oCastlingRights, 
        Square_T oEnpSqr, size_t halfMoveCount, UndoInfo_T oUndoInfo)
{
    CHECK_NULL(oMove);
    CHECK_NULL(oCastlingRights);

    UndoInfo_T undo = (UndoInfo_T)calloc(1, sizeof(struct UndoInfo));
    CHECK_MEM(undo);

    undo->move = Move_copy(oMove);
    undo->prevCastlingRights = Castles_copy(oCastlingRights);
    if (oEnpSqr != NULL)
        undo->prevEnpSquare = Square_copy(oEnpSqr);
    undo->prevHalfmoveClock = halfMoveCount;
    undo->prevUndo = oUndoInfo;

    undo->wasCapture = false;
    undo->capturedSquare = NULL;
    undo->capturedPieceColor = NO_COLOR;
    undo->capturedPieceType = NO_TYPE;

    undo->wasCastle = false;
    
    undo->wasEnpMove = false; // needed?
    
    undo->wasPromotion = false;
    undo->promotedFromType = NO_TYPE;

    return undo;
}
void UndoInfo_free (UndoInfo_T undo)
{
    CHECK_NULL(undo);

    Move_free(undo->move);
    Castles_free(undo->prevCastlingRights);
    if (undo->capturedSquare != NULL)
        Square_free(undo->capturedSquare);
    if (undo->prevEnpSquare != NULL)
        Square_free(undo->prevEnpSquare);

    free(undo);
}
UndoInfo_T UndoInfo_copy (UndoInfo_T undo)
{
    CHECK_NULL(undo);
    UndoInfo_T uCopy = UndoInfo_new(undo->move, undo->prevCastlingRights, 
            undo->prevEnpSquare, undo->prevHalfmoveClock, undo->prevUndo);

    if (undo->wasCapture)
        UndoInfo_logCapture(uCopy, undo->capturedSquare, undo->capturedPieceType, undo->capturedPieceColor);
    
    if (undo->wasEnpMove)
        UndoInfo_logEnpassant(uCopy);
    
    if (undo->wasCapture)
        UndoInfo_logCastle(uCopy);

    if (undo->wasPromotion)
        UndoInfo_logPromotion(uCopy, undo->promotedFromType);

    return uCopy;
}

void UndoInfo_logCapture (UndoInfo_T undo, Square_T sqr, p_type type, p_color color)
{
    CHECK_NULL(undo);
    CHECK_NULL(sqr);

    undo->wasCapture = true;
    undo->capturedSquare = Square_copy(sqr);
    undo->capturedPieceType = type;
    undo->capturedPieceColor = color;
}
void UndoInfo_logEnpassant (UndoInfo_T undo)
{
    CHECK_NULL(undo);

    undo->wasEnpMove = true;
}
void UndoInfo_logCastle (UndoInfo_T undo)
{
    CHECK_NULL(undo);

    undo->wasCastle = true;
}
void UndoInfo_logPromotion (UndoInfo_T undo, p_type fromType)
{
    CHECK_NULL(undo);

    undo->wasPromotion = true;
    undo->promotedFromType = fromType;
}

Move_T      UndoInfo_getMove          (UndoInfo_T undo)
{
    return undo->move;
}
Castles_T   UndoInfo_getCastling      (UndoInfo_T undo)
{
    return undo->prevCastlingRights;
}
Square_T    UndoInfo_getEnpSqr        (UndoInfo_T undo)
{
    return undo->prevEnpSquare;
}
size_t      UndoInfo_getHalfMClock    (UndoInfo_T undo)
{
    return undo->prevHalfmoveClock;
}
UndoInfo_T  UndoInfo_getNextUndo      (UndoInfo_T undo)
{
    return undo->prevUndo;
}

bool        UndoInfo_getWasEnpMove    (UndoInfo_T undo)
{
    return undo->wasEnpMove;
}
bool        UndoInfo_getWasCastleMove (UndoInfo_T undo)
{
    return undo->prevEnpSquare;
}
bool        UndoInfo_getWasPromotion  (UndoInfo_T undo)
{
    return undo->wasPromotion;
}
bool        UndoInfo_getWasCapture    (UndoInfo_T undo)
{
    return undo->wasCapture;
}

p_color     UndoInfo_getCaptureColor  (UndoInfo_T undo)
{
    return undo->capturedPieceColor;
}
p_type      UndoInfo_getCaptureType   (UndoInfo_T undo)
{
    return undo->capturedPieceType;
}
Square_T    UndoInfo_getCaptureSqr    (UndoInfo_T undo)
{
    return undo->capturedSquare;
}
p_type      UndoInfo_getPromotionType (UndoInfo_T undo)
{
    return undo->promotedFromType;
}


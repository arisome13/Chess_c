/*--------------------------------------------------------------------*/
/* undoinfo.c                                                         */
/*--------------------------------------------------------------------*/

#include "undoinfo.h"

struct UndoInfo 
{
    Move_T      move;
    Castles_T   prevCastlingRights;
    size_t      prevHalfmoveClock;

    // captures
    bool        wasCapture;
    p_color     capturedPieceColor;
    p_type      capturedPieceType;
    Square_T    capturedSquare;

    // enpassant
    bool        wasEnPassant;
    Square_T    enPassantSquare;
    
    // castle
    bool        wasCastle;

    // promotion
    bool        wasPromotion;
    p_type      promotedFromType;
};

UndoInfo_T UndoInfo_new (Move_T oMove, Castles_T oCastlingRights, size_t halfMoveCount)
{
    CHECK_NULL(oCastlingRights);

    UndoInfo_T undo = (UndoInfo_T)calloc(1, sizeof(struct UndoInfo));
    CHECK_MEM(undo);

    undo->move = Move_copy(oMove);
    undo->prevCastlingRights = Castles_copy(oCastlingRights);
    undo->prevHalfmoveClock = halfMoveCount;

    undo->wasCapture = false;
    undo->capturedSquare = NULL;
    undo->capturedPieceColor = NO_COLOR;
    undo->capturedPieceType = NO_TYPE;

    undo->wasCastle = false;
    
    undo->wasEnPassant = false;
    undo->enPassantSquare = NULL;
    
    undo->wasPromotion = false;
    undo->promotedFromType = NO_TYPE;

    return undo;
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

void UndoInfo_logEnpassant (UndoInfo_T undo, Square_T enpsqr)
{
    CHECK_NULL(undo);
    CHECK_NULL(enpsqr);

    undo->wasEnPassant = true;
    undo->enPassantSquare = Square_copy(enpsqr);
}

void UndoInfo_logCastle (UndoInfo_T undo, bool wasCastle)
{
    CHECK_NULL(undo);

    undo->wasCastle = wasCastle;
}

void UndoInfo_logPromotion (UndoInfo_T undo, p_type fromType)
{
    CHECK_NULL(undo);

    undo->wasPromotion = true;
    undo->promotedFromType = fromType;
}


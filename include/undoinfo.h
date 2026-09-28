/*--------------------------------------------------------------------*/
/* undoinfo.h                                                         */
/*--------------------------------------------------------------------*/

#ifndef UNDOINFO_H
#define UNDOINFO_H

#include "move.h"
#include "castles.h"

/* holds all the necessary information to undo a move 
    made by a chess Engine_T */
typedef struct UndoInfo *UndoInfo_T;

/* Return a new UndoInfo_T object. The appropriate object values with the 
    given parameters, and the rest of the object values as null. */
UndoInfo_T UndoInfo_new (Move_T oMove, Castles_T oCastlingRights, size_t halfMoveCount);

/* Initialize the appropriate object values. */
void UndoInfo_logCapture (UndoInfo_T undo, Square_T sqr, p_type type, p_color color);
void UndoInfo_logEnpassant (UndoInfo_T undo, Square_T enpsqr);
void UndoInfo_logCastle (UndoInfo_T undo, bool wasCastle);
void UndoInfo_logPromotion (UndoInfo_T undo, p_type fromType);
void UndoInfo_logHalfMoveCount (UndoInfo_T undo, size_t halfMoveCount);

#endif

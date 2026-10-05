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
UndoInfo_T UndoInfo_new (Move_T oMove, Castles_T oCastlingRights, Square_T oEnpSqr, size_t halfMoveCount, UndoInfo_T oUndoInfo);

/* Free the undo object and all relavent memory. */
void UndoInfo_free (UndoInfo_T undo);

/* Return a deep copy of undo info object. */
UndoInfo_T UndoInfo_copy (UndoInfo_T undo);

/* Initialize the appropriate object values. */
void UndoInfo_logCapture (UndoInfo_T undo, Square_T sqr, p_type type, p_color color);
void UndoInfo_logEnpassant (UndoInfo_T undo);
void UndoInfo_logCastle (UndoInfo_T undo);
void UndoInfo_logPromotion (UndoInfo_T undo, p_type fromType);

/* getters */

Move_T      UndoInfo_getMove          (UndoInfo_T undo);
Castles_T   UndoInfo_getCastling      (UndoInfo_T undo);
Square_T    UndoInfo_getEnpSqr        (UndoInfo_T undo);
size_t      UndoInfo_getHalfMClock    (UndoInfo_T undo);
UndoInfo_T  UndoInfo_getNextUndo      (UndoInfo_T undo);

bool        UndoInfo_getWasEnpMove    (UndoInfo_T undo);
bool        UndoInfo_getWasCastleMove (UndoInfo_T undo);
bool        UndoInfo_getWasPromotion  (UndoInfo_T undo);
bool        UndoInfo_getWasCapture    (UndoInfo_T undo);

p_color     UndoInfo_getCaptureColor  (UndoInfo_T undo);
p_type      UndoInfo_getCaptureType   (UndoInfo_T undo);
Square_T    UndoInfo_getCaptureSqr    (UndoInfo_T undo);
p_type      UndoInfo_getPromotionType (UndoInfo_T undo);

#endif

/*--------------------------------------------------------------------*/
/* movepattern.h                                                      */
/*--------------------------------------------------------------------*/

#include "helpers.h"
#include <mask.h>
#include <move.h>

#ifndef MOVEPATTERN_INCLUDED
#define MOVEPATTERN_INCLUDED

/* A MovePattern_T object holds the different types of moves a piece 
    can make. */
typedef struct MovePattern *MovePattern_T;

/*--------------------------------------------------------------------*/

/* Return a new MovePattern_T object initialized to empty. 
    CALLER FREE. */
MovePattern_T MovePattern_new (void);

/* Free oPattern. */
void MovePattern_free (MovePattern_T oPattern);

/* Return a deep copy of oPattern. CALLER FREE. */
MovePattern_T MovePattern_copy (MovePattern_T oPattern);

/*--------------------------------------------------------------------*/

/* Adds a move in direction (dx, dy) to oPattern. */
void MovePattern_add (MovePattern_T oPattern, 
    int dx, int dy, bool repeating);

/* Returns a mask of the squares oMove goes through, or NULL if the 
    move cannot be made with oPattern. CALLER FREE. */
Mask_T MovePattern_canMove (MovePattern_T oPattern, Move_T oMove);

/* Returns the move pattern for the given pieceName. CALLER FREE. */
MovePattern_T MovePattern_for (char pieceName);

/*--------------------------------------------------------------------*/

/* Return a string representation of oPattern. CALLER FREE. */
char *MovePattern_toString (MovePattern_T oPattern);

#endif
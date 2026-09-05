/*--------------------------------------------------------------------*/
/* movepattern.h                                                      */
/*--------------------------------------------------------------------*/

#include "helpers.h"

#ifndef MOVEPATTERN_INCLUDED
#define MOVEPATTERN_INCLUDED

/* A MovePattern_T object holds the different types of moves a piece 
    can make. */
typedef struct MovePattern *MovePattern_T;

/* Return a new MovePattern_T object initialized to empty. Raises error if
    insufficient memory is available. */
MovePattern_T MovePattern_new (void);

/* Free oPattern. */
void MovePattern_free (MovePattern_T oPattern);

/* Adds a move int direction (x, y) to oPattern. */
void MovePattern_add (MovePattern_T oPattern, int x, int y, bool repeating);

///* Return a deep copy of oCastles. Caller must free. */
//MovePattern_T MovePattern_copy (MovePattern_T oCastles);

/* Return a string representation of oPattern. Caller free. */
char *MovePattern_toString (MovePattern_T oPattern);

#endif
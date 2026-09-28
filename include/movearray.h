/*--------------------------------------------------------------------*/
/* movearray.h                                                        */
/*--------------------------------------------------------------------*/

#include "move.h"

#ifndef MOVEARRAY_H
#define MOVEARRAY_H

/* A MoveArray_T object is an array that holds at most 256 moves. */
typedef struct MoveArray *MoveArray_T;

enum {MAX_MOVES_IN_ARRAY = 256};

/*--------------------------------------------------------------------*/

/* Return a new MoveArray_T object initialized to empty. CALLER FREE. */
MoveArray_T MoveArray_new (void);

/* Free omArray. */
void MoveArray_free (MoveArray_T omArray);

/* Return a deep copy of omArray. CALLER FREE. */
// MoveArray_T MoveArray_copy (MoveArray_T omArray);

/*--------------------------------------------------------------------*/

/* Adds a move to omArray. Raises an error if it is already at the 
    maximum number of moves. */
void MoveArray_add (MoveArray_T omArray, Move_T oMove);

/* Returns the move at position "index" of omArray. Raises and error
    if the position is outside the possible bounds, returns NULL if 
    the "index" is greater than the number of moves in the array. */
Move_T MoveArray_get (MoveArray_T omArray, size_t index);

/*--------------------------------------------------------------------*/

/* Return a string representation of omArray. CALLER FREE. */
char *MoveArray_toString (MoveArray_T omArray);

#endif

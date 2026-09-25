/*--------------------------------------------------------------------*/
/* move.h                                                             */
/*--------------------------------------------------------------------*/

#include "square.h"

#ifndef MOVE_H
#define MOVE_H

/* A Move_T object holds the location of source and destination 
    squares. */
typedef struct Move *Move_T;

/*--------------------------------------------------------------------*/

/* Return a new Move_T object initialized to the given parameters.
    Client is responsible for freeing src and dst. CALLER FREE. */
Move_T Move_new(Square_T src, Square_T dst);

/* Return a new Move_T object initialized to the given pcNotation. 
    CALLER FREE. */
Move_T Move_read(const char *pcNotation);

/* Free oMove. */
void Move_free(Move_T oMove);

/* Free oMove without freeing oMove's squares. */
void Move_free_minimal(Move_T oMove);

/* Return a copy of oMove. CALLER FREE. */
Move_T Move_copy (Move_T oMove);

/* Place a copy of mSrc into mDst. */
void Move_copyTo (Move_T mSrc, Move_T mDst);

/*--------------------------------------------------------------------*/

/* Returns the source or destination squares of the oMove object. */
Square_T Move_src(Move_T oMove);
Square_T Move_dst(Move_T oMove);

/*--------------------------------------------------------------------*/

/* Return whether oMove1 contians the same location as oMove2. */
bool Move_equals(Move_T oMove1, Move_T oMove2);

/* Return the string representation of oMove, or NULL if insufficient 
    memory is available. CALLER FREE. */
char *Move_toString(Move_T oMove);

#endif

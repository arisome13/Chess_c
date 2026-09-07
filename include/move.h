/*--------------------------------------------------------------------*/
/* move.h                                                             */
/*--------------------------------------------------------------------*/

#include "square.h"

#ifndef MOVE_INCLUDED
#define MOVE_INCLUDED

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

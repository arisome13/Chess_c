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

/* Return a new Move_T object initialized to the given parameters, or 
    NULL if insufficient memory is available. Client becomes responsible
    for freeing src and dst after use. */
Move_T Move_new(Square_T src, Square_T dst);
  
/* Free oMove. */
void Move_free(Move_T oMove);

/*--------------------------------------------------------------------*/

/* Return whether oMove1 contians the same location as oMove2. */
bool Move_equals(Move_T oMove1, Move_T oMove2);

/* Return the string representation of oMove, or NULL if insufficient 
    memory is available. Caller must free. */
char *Move_toString(Move_T oMove);

#endif

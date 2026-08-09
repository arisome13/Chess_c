/*--------------------------------------------------------------------*/
/* engine.h                                                           */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include "board.h"
#include "parameters.h"
#include "move.h"

#ifndef ENGINE_INCLUDED
#define ENGINE_INCLUDED

/* An Engine_T is a pointer to a chess engine capable of both holding a 
    chess position and finding the best possible move from that 
    position. */

typedef struct Engine *Engine_T;

/*--------------------------------------------------------------------*/

/* Return a new Engine_T object initialized to pcFen parrameters, or 
   NULL if insufficient memory is available. */

Engine_T Engine_new(const char *pcFen);

/*--------------------------------------------------------------------*/

/* Free oEngine. */

void Engine_free(Engine_T oEngine);

/*--------------------------------------------------------------------*/

/* Returns the best move in the chess position held by the engine's
   chess board. */

Move_T Engine_bestMove (Engine_T oEngine);

/*--------------------------------------------------------------------*/

/* Return the string representation of oBoard. Caller must free. */

char *Engine_toString (Engine_T oEngine);

#endif
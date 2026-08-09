/*--------------------------------------------------------------------*/
/* engine.h                                                           */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include "board.h"

#ifndef ENGINE_INCLUDED
#define ENGINE_INCLUDED

/* An Engine_T is a pointer to a chess engine capable of both holding a 
    chess position and finding the best possible move from that 
    position. */

struct Engine
{
   /* A chess board object holding the pieces on the board */
   ChessBoard_T oBoard;
   
   /* PARAM 2 */
   unsigned long aulDigits[3];
};

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

int Engine_bestMove (Engine_T oEngine);

/*--------------------------------------------------------------------*/

/* FUNCTION DESCRIPTION */

int Engine_func (Engine_T oEngine/*, OTHER PARAMETERS*/);

#endif
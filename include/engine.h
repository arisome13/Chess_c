/*--------------------------------------------------------------------*/
/* engine.h                                                           */
/*--------------------------------------------------------------------*/

#include "move.h"
#include "states.h"
#include "eval.h"
#include "movearray.h"

#ifndef ENGINE_H
#define ENGINE_H

/* An Engine_T is a pointer to a chess engine capable of both holding a 
   chess position and finding the best possible move from that 
   position. */
typedef struct Engine *Engine_T;

/* the starting fen for a general chess board */
#define STARTING_FEN    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

/*--------------------------------------------------------------------*/

/* Return a new Engine_T object initialized to pcFen parrameters, or 
   the normal chess starting position if pcFen is NULL. CALLER FREE */
Engine_T Engine_new(const char *pcFen);

/* Free oEngine. */
void Engine_free(Engine_T oEngine);

/* Return a deep copy of oEngine. CALLER FREE. */
Engine_T Engine_copy (Engine_T oEngine);

/*--------------------------------------------------------------------*/

/* undo the last move */
void Engine_undo (Engine_T oEngine);

/* Fill a MoveArray_T with the legal moves for oEngine and return it. 
   CALLER FREE. */
MoveArray_T Engine_legalMoves (Engine_T oEngine);

/* Evaluate oEngine's position by searching possible moves. Returns NULL
   if there are no legal moves. CALLER FREE. */
Eval_T Engine_evaluate (Engine_T oEngine);

/* Returns the best move in the chess position held by the engine's
   chess board. CALLER FREE. */
Move_T Engine_bestMove (Engine_T oEngine);

/* Make oMove on oEngine's chess board. */
s_move Engine_makeMove (Engine_T oEngine, Move_T oMove);

/* Set how deep the engine searches to find the best move. 0 < d < 8 */
void Engine_setDepth (Engine_T oEngine, size_t d);

/*--------------------------------------------------------------------*/

char *Engine_notation (Engine_T oEngine, Move_T oMove);

/* Return the string representation of oBoard. CALLER FREE. */
char *Engine_toString (Engine_T oEngine);

#endif
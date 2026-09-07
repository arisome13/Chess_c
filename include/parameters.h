/*--------------------------------------------------------------------*/
/* parameters.h                                                       */
/*--------------------------------------------------------------------*/

#include "square.h"
#include "castles.h"
#include "color.h"

#ifndef PARAMETERS_INCLUDED
#define PARAMETERS_INCLUDED

/* A ChessParameters_T object defines the state of a chess game. */
typedef struct ChessParameters *ChessParameters_T;

/*--------------------------------------------------------------------*/

/* Return a new ChessParameters_T object initialized to the pcFen
   parameters. CALLER FREE. */
ChessParameters_T ChessParameters_new(const char *pcFen);

/* Free oParams. */
void ChessParameters_free(ChessParameters_T oParams);

/* Return a deep copy of oParams. CALLER FREE. */
ChessParameters_T ChessParameters_copy(ChessParameters_T oParams);

/*--------------------------------------------------------------------*/

/* Return the turn color. */
color ChessParameters_turnColor(ChessParameters_T oParams);

/* Return the available castles as a castles struct. */
Castles_T ChessParameters_castles(ChessParameters_T oParams);

/* Return the enpassant square as a 6 bit number, or NULL if no
   enpassant square exists. */
Square_T ChessParameters_enpSqr(ChessParameters_T oParams);

/* Return the number of half moves since a capture or pawn move. */
int ChessParameters_50MoveRule(ChessParameters_T oParams);

/* Return the move number of the current move being played. */
int ChessParameters_numMoves(ChessParameters_T oParams);

/*--------------------------------------------------------------------*/

/* Return the string representation of the oParams object. 
   CALLER FREE. */
char *ChessParameters_toString(ChessParameters_T oParams);

#endif

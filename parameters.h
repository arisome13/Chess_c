/*--------------------------------------------------------------------*/
/* parameters.h                                                       */
/*--------------------------------------------------------------------*/

#include "square.h"
#include "helpers.h"

#ifndef PARAMETERS_INCLUDED
#define PARAMETERS_INCLUDED

/* A ChessParameters_T object defines the state of a chess game. */
struct ChessParameters
{
   /* color of the current play*/
   enum color cTurnColor;

   /* available castle indicators */
   char *pcCastles;

   /* enpassant square */
   Square_T sqrEnpassant;

   /* half move count for 50 move rule */
   int i50MoveCount;

   /* current full move */
   int iCurrMove;
};
typedef struct ChessParameters *ChessParameters_T;

/*--------------------------------------------------------------------*/

/* Return a new ChessParameters_T object initialized to the pcFen
   parameters, or NULL if insufficient memory is available. */
ChessParameters_T ChessParameters_new(char *pcFen);

/* Free oParams. */
void ChessParameters_free(ChessParameters_T oParams);

/*--------------------------------------------------------------------*/

/* Return the turn color. */
enum color ChessParameters_turnColor(ChessParameters_T oParams);

/* Return the available castles as a 4 bit number. */
char *ChessParameters_castles(ChessParameters_T oParams);

/* Return the enpassant square as a 6 bit number, or NULL if no
   enpassant square exists. */
Square_T ChessParameters_enpSqr(ChessParameters_T oParams);

/* Return the number of half moves since a capture or pawn move. This
   number will always be under 50 so can be stored as a 6 bit number. */
int ChessParameters_50MoveRule(ChessParameters_T oParams);

/* Return the move number of the current move being played. */
int ChessParameters_numMoves(ChessParameters_T oParams);

/*--------------------------------------------------------------------*/

/* Return the string representation of the oParams object. */
char *ChessParameters_toString(ChessParameters_T oParams);

#endif

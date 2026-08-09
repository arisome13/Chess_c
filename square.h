/*--------------------------------------------------------------------*/
/* square.h                                                           */
/*--------------------------------------------------------------------*/

#ifndef SQUARE_INCLUDED
#define SQUARE_INCLUDED

#include "helpers.h"

/* A Square_T object holds the location of a square on a chess board. */

typedef struct Square *Square_T;

/*--------------------------------------------------------------------*/

/* Return a new Square_T object initialized to the given parameters, or 
    NULL if insufficient memory is available. */
Square_T Square_initCoords(int rank, int file);
Square_T Square_initNotation(char *pcNotation);

/* Free oSquare. */
void Square_free(Square_T oSquare);

/*--------------------------------------------------------------------*/

/* Return whether oSquare1 contians the same location as oSquare2. */
bool Square_equals(Square_T oSquare1, Square_T oSquare2);

/* Return the algebraic notation for the square oSquare represents,
    or NULL if insufficient memory is available. Caller must free. */
char *Square_getNotation(Square_T oSquare);

#endif

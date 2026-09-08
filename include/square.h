/*--------------------------------------------------------------------*/
/* square.h                                                           */
/*--------------------------------------------------------------------*/

#include "helpers.h"

#ifndef SQUARE_INCLUDED
#define SQUARE_INCLUDED

/* A Square_T object holds the location of a square on a chess board. */
struct Square
{
    /* rank = 8 - y */
    size_t y;

    /* file = x */
    size_t x;
};
typedef struct Square *Square_T;


/*--------------------------------------------------------------------*/

/* Return a new Square_T object initialized to the given parameters. 
    CALLER FREE. */
/* coords are defined from the top left rank: 0-7, file: 0-7 */
Square_T Square_newCoords(size_t y, size_t x);
/* notation is defined from bottom left rank: 1-8, file: a-h */
Square_T Square_newNotation(const char *pcNotation);

/* Free oSquare. */
void Square_free(Square_T oSquare);

/* Return a deep copy of oSquare. CALLER FREE. */
Square_T Square_copy(Square_T oSquare);

/*--------------------------------------------------------------------*/

/* Return whether oSquare1 contians the same location as oSquare2. */
bool Square_equals(Square_T oSquare1, Square_T oSquare2);

/* Return the algebraic notation for the square oSquare represents,
    or NULL if insufficient memory is available. CALLER FREE. */
char *Square_toString(Square_T oSquare);

#endif

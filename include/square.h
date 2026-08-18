/*--------------------------------------------------------------------*/
/* square.h                                                           */
/*--------------------------------------------------------------------*/

#ifndef SQUARE_INCLUDED
#define SQUARE_INCLUDED

#include "helpers.h"

/* A Square_T object holds the location of a square on a chess board. */
struct Square
{
    /* rank */
    int iRank;

    /* file */
    int iFile;
};
typedef struct Square *Square_T;

/*--------------------------------------------------------------------*/

/* Return a new Square_T object initialized to the given parameters, or 
    NULL if insufficient memory is available. */
    /* coords are defined from the top left 
        rank: 0-7, file: 0-7 */
Square_T Square_newCoords(int rank, int file);
    /* notation is defined from bottom left 
        rank: 1-8, file: a-h */
Square_T Square_newNotation(char *pcNotation);

/* Free oSquare. */
void Square_free(Square_T oSquare);

/*--------------------------------------------------------------------*/

/* Return whether oSquare1 contians the same location as oSquare2. */
bool Square_equals(Square_T oSquare1, Square_T oSquare2);

/* Return the position on a bit board the oSquare object represents. */
int Square_bitPos(Square_T oSquare);

/* Return a mask of the position of the oSquare object. */
uint64_t Square_bitMask(Square_T oSquare);

/* Return the algebraic notation for the square oSquare represents,
    or NULL if insufficient memory is available. Caller must free. */
char *Square_getNotation(Square_T oSquare);

#endif

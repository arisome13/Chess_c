/*--------------------------------------------------------------------*/
/* map.h                                                             */
/*--------------------------------------------------------------------*/

#include "move.h"
#include "mask.h"

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

/* A Map_T object holds the piece positions of a single piece on 
    a chess board. */
typedef struct Map *Map_T;
/* A MapFunction is a function with a single map pointer parameter
    and returns nothing. */
typedef void (*MapFunction)(Map_T, int*);

/*--------------------------------------------------------------------*/

/* Return a new Map_T object initialized to empty. CALLER FREE. */
Map_T Map_new(char name);

/* Free oMap. */
void Map_free(Map_T oMap);

/* Return a deep copy of oMap. CALLER FREE. */
Map_T Map_copy (Map_T oMap);

/*--------------------------------------------------------------------*/

/* Return oMap's corresponding char name. */
char Map_getName(Map_T oMap);

/* Return how many pieces are held in oMap. */
int Map_numPieces(Map_T oMap);

/* Return the color of the piece type oMap holds. */
color Map_color(Map_T oMap);

/*--------------------------------------------------------------------*/

/* Alter oMap so that there is a 1 in the spot corresponding to sqr. */
void Map_place(Map_T oMap, Square_T oSqr);

/* Alter oMap so that there is a 0 in the spot corresponding to sqr. */
void Map_remove(Map_T oMap, Square_T oSqr);

/*--------------------------------------------------------------------*/

/* Returns whether the given location holds a piece. */
bool Map_isCovered_coords(Map_T oMap, int x, int y);
bool Map_isCovered_sqr(Map_T oMap, Square_T oSqr);

/* Add the value of the pieces in oMap to iTotal. */
void Map_addUpPieces (Map_T oMap, int *iTotal);

/* Returns an empty or populated list of the squares oMap's piece would 
    have to cross to get to the destination. If it is NULL, the move 
    cannot be made. CALLER FREE. */
Mask_T Map_hasRangeTo (Map_T oMap, Move_T oMove);

/* Returns true if both oMap and oMask have at least one filled sqr in 
    the same location, false otherwise. */
bool Map_shareSqr (Map_T oMap, Mask_T oMask);

/*--------------------------------------------------------------------*/

/* Return the string representation of the ullMap. CALLER FREE. */
char *Map_toString(Map_T oMap);

#endif

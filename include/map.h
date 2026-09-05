/*--------------------------------------------------------------------*/
/* map.h                                                             */
/*--------------------------------------------------------------------*/

#include <stdint.h>
#include "helpers.h"
#include "square.h"

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

/* A Map_T object holds the piece positions of a single piece on 
    a chess board. */
typedef struct Map *Map_T;
/* A MapFunction is a function with a single map pointer parameter
    and returns nothing. */
typedef void (*MapFunction)(Map_T, int*);

/*--------------------------------------------------------------------*/

/* Return a new Map_T object initialized to the given parameters, or 
    NULL if insufficient memory is available. */
Map_T Map_new(char name);

/* Free oMap. */
void Map_free(Map_T oMap);

/* Return a deep copy of oMap. Caller must free. */
Map_T Map_copy (Map_T oMap);

/*--------------------------------------------------------------------*/

/* Return oMap's corresponding char name. */
char Map_getName(Map_T oMap);

/* Return how many pieces are held in oMap. */
int Map_numPieces(Map_T oMap);

/* Return the map's piece position map. */
uint64_t Map_getPos(Map_T oMap);

/*--------------------------------------------------------------------*/

/* Alter oMap so that there is a 1 in the spot corresponding to sqr. */
void Map_place(Map_T oMap, Square_T oSqr);

/* Alter oMap so that there is a 0 in the spot corresponding to sqr. */
void Map_capture(Map_T oMap, Square_T oSqr);

/*--------------------------------------------------------------------*/

/* Returns whether the location r,f holds a piece. */
bool Map_isCovered(Map_T oMap, int r, int f);

/* Add the value of the pieces in oMap to iTotal. */
void Map_addUpPieces (Map_T oMap, int *iTotal);

/*--------------------------------------------------------------------*/

/* Return the string representation of the ullMap. */
char *Map_toString(Map_T oMap);

#endif

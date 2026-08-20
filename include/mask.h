/*--------------------------------------------------------------------*/
/* mask.h                                                             */
/*--------------------------------------------------------------------*/

#include <stdint.h>
#include "helpers.h"
#include "square.h"

#ifndef MASK_INCLUDED
#define MASK_INCLUDED

/* A Mask_T object holds the piece positions of a single piece on 
    a chess board. */
typedef struct Mask *Mask_T;
/* A MaskFunction is a function with a single mask pointer parameter
    and returns nothing. */
typedef void (*MaskFunction)(Mask_T, int*);

/*--------------------------------------------------------------------*/

/* Return a new Mask_T object initialized to the given parameters, or 
    NULL if insufficient memory is available. */
Mask_T Mask_new(char name);
  
/* Free oMask. */
void Mask_free(Mask_T oMask);

/* Return a deep copy of oMask. Caller must free. */
Mask_T Mask_copy (Mask_T oMask);

/*--------------------------------------------------------------------*/

/* Return oMask's corresponding char name. */
char Mask_getName(Mask_T oMask);

/* Return how many pieces are held in oMask. */
int Mask_numPieces(Mask_T oMask);

/* Return the mask's piece position mask. */
uint64_t Mask_getPos(Mask_T oMask);

/*--------------------------------------------------------------------*/

/* Alter oMask so that there is a 1 in the spot corresponding to sqr. */
void Mask_place(Mask_T oMask, Square_T oSqr);

/* Alter oMask so that there is a 0 in the spot corresponding to sqr. */
void Mask_capture(Mask_T oMask, Square_T oSqr);

/*--------------------------------------------------------------------*/

/* Returns whether the location r,f holds a piece. */
bool Mask_isCovered(Mask_T oMask, int r, int f);

/*--------------------------------------------------------------------*/

/* Return the string representation of the ullMask. */
char *Mask_toString(Mask_T oMask);

#endif

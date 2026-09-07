/*--------------------------------------------------------------------*/
/* mask.h                                                             */
/*--------------------------------------------------------------------*/

#include "helpers.h"

#ifndef MASK_INCLUDED
#define MASK_INCLUDED

/* A Mask_T object holds a bit (either 0 or 1) of information for each 
    square on an 8x8 grid. The grid is accessed using the coordinates
    (x, y) with the top left defined as (0, 0). */
typedef struct Mask *Mask_T;

/*--------------------------------------------------------------------*/
// INITIALIZATION

/* Return a new Mask_T object initialized to empty. CALLER FREE. */
Mask_T Mask_new(void);

/* Free oMask. */
void Mask_free(Mask_T oMask);

/* Return a deep copy of oMask. CALLER FREE. */
Mask_T Mask_copy (Mask_T oMask);

/* Resets oMask's grid to hold only 0s (nothing/empty). */
void Mask_reset (Mask_T oMask);

/*--------------------------------------------------------------------*/
// INFORMATION

/* Return how many squares on oMask are turned on (have a 1). */
size_t Mask_count(Mask_T oMask);

/* Returns true if (x, y) on oMask is on, false otherwise. */
bool Mask_isSet(Mask_T oMask, size_t x, size_t y);

/* Returns true if at least one square is shared. */
bool Mask_shareSqr(Mask_T oMask1, Mask_T oMask2);

/*--------------------------------------------------------------------*/
// ALTERATION

/* Set the square on oMask at (x, y): x, y in [0, 7] */
void Mask_set(Mask_T oMask, size_t x, size_t y, enum ON_OFF onORoff);

/*--------------------------------------------------------------------*/
// DESCRIPTION

/* Return the string representation of the oMask. CALLER FREE. */
char *Mask_toString(Mask_T oMask);

#endif

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

/*--------------------------------------------------------------------*/

/* Return a new Mask_T object initialized to the given parameters, or 
    NULL if insufficient memory is available. */
   
Mask_T Mask_new(char *name);
  
/*--------------------------------------------------------------------*/

/* Free oMask. */

void Mask_free(Mask_T oMask);

/*--------------------------------------------------------------------*/

/* Return whether the mask is for the given piece. */

bool Mask_matchesName(Mask_T oMask, char *name);

/*--------------------------------------------------------------------*/

/* Return the mask's piece position mask. */

uint64_t Mask_getPos(Mask_T oMask);

/*--------------------------------------------------------------------*/

/* Return the mask's piece position mask. */

void Mask_place(Mask_T oMask, Square_T pos);

/*--------------------------------------------------------------------*/

/* Return the string representation of the ullMask. */

char *Mask_toString(Mask_T oMask);

#endif

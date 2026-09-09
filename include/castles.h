/*--------------------------------------------------------------------*/
/* castles.h                                                          */
/*--------------------------------------------------------------------*/

#include "helpers.h"

#ifndef CASTLES_INCLUDED
#define CASTLES_INCLUDED

/* A Castles_T object holds the castles a given chess position can 
    allow. */
typedef struct Castles *Castles_T;

/* Return a new Castles_T object initialized to empty. CALLER FREE. */
Castles_T Castles_new (void);

/* Free oCastles. */
void Castles_free (Castles_T oCastles);

/* Return a deep copy of oCastles. CALLER FREE. */
Castles_T Castles_copy (Castles_T oCastles);

/* Adds the given castleType to oCastles. Raises error if already added. */
void Castles_add (Castles_T oCastles, char castleType);

/* Removes the given castleType from oCastles. Raises error if nonexistant. */
void Castles_remove (Castles_T oCastles, char castleType);


/* Return a string representation of oCastles. */
const char *Castles_toString (Castles_T oCastles);

#endif
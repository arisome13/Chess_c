/*--------------------------------------------------------------------*/
/* type.h                                                           */
/*--------------------------------------------------------------------*/

#include "color.h"

#ifndef TYPE_INCLUDED
#define TYPE_INCLUDED

typedef enum p_type {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NO_TYPE} p_type;

/* returns the value of the given chess piece */
int Type_getValue (p_type type, p_color color);

/* returns a char representation of the given chess piece */
char Type_toString(p_type type, p_color color);

#endif
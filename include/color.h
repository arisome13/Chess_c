/*--------------------------------------------------------------------*/
/* color.h                                                           */
/*--------------------------------------------------------------------*/

#ifndef COLOR_INCLUDED
#define COLOR_INCLUDED

typedef enum color {BLACK, WHITE} color;

/* Returns the string representation of color c. */
const char *Color_toString(color c);

#endif
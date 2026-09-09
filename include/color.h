/*--------------------------------------------------------------------*/
/* color.h                                                           */
/*--------------------------------------------------------------------*/

#ifndef COLOR_INCLUDED
#define COLOR_INCLUDED

typedef enum p_color {BLACK, WHITE, NO_COLOR} p_color;

/* Returns the string representation of color c. */
const char *Color_toString(p_color c);

#endif
/*--------------------------------------------------------------------*/
/* color.h                                                           */
/*--------------------------------------------------------------------*/

#ifndef COLOR_H
#define COLOR_H

typedef enum p_color {BLACK, WHITE, NO_COLOR} p_color;

/* Returns the oposite color of c. */
p_color Color_oposite(p_color c);

/* Returns the string representation of color c. */
const char *Color_toString(p_color c);

#endif
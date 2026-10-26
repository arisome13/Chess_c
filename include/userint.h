/*--------------------------------------------------------------------*/
/* userint.h                                                          */
/*--------------------------------------------------------------------*/

#ifndef USERINT_H
#define USERINT_H

#include "helpers.h"
#include "square.h"

typedef void (*SendMove_func)(size_t fromY, size_t fromX, size_t toY, size_t toX);

/* Starts the chess ui window and sends it the sendfunc to call when 
    a move is made by the user. */
void ChessUI_run(SendMove_func sendfunc);

/* Loads the given inputcharboard to the chess ui and  
    updates the ui visual. Highlight s1 and s2. */
void ChessUI_load(CharBoard inputboard, Square_T s1, Square_T s2);

#endif
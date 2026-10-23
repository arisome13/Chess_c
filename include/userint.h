/*--------------------------------------------------------------------*/
/* userint.h                                                          */
/*--------------------------------------------------------------------*/

#ifndef USERINT_H
#define USERINT_H

#include "helpers.h"

typedef void (*SendMove_func)(size_t fromY, size_t fromX, size_t toY, size_t toX);

/* Starts the chess ui window and sends it the sendfunc to call when 
    a move is made by the user. endfunc is called when the window 
    is closed. */
void ChessUI_run(SendMove_func sendfunc, void (*endfunc)(void));

/* Loads the given inputcharboard to the chess ui and  
    updates the ui visual. */
void ChessUI_load(CharBoard inputboard);

#endif
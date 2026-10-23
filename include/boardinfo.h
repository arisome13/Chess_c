/*--------------------------------------------------------------------*/
/* boardinfo.h                                                        */
/*--------------------------------------------------------------------*/

#include "helpers.h"

#ifndef BOARDINFO_H
#define BOARDINFO_H

typedef struct BoardInfo *BoardInfo_T;

/*--------------------------------------------------------------------*/

/* Return a new BoardInfo_T object initialized to empty. 
    CALLER FREE. */
BoardInfo_T BoardInfo_new(void);

/* Free bInfo. */
void BoardInfo_free(BoardInfo_T bInfo);

/*--------------------------------------------------------------------*/

/* Retrieve the char at (y,x) */
char BoardInfo_get(BoardInfo_T bInfo, size_t y, size_t x);

/* Assign the char at (y,x) */
void BoardInfo_set(BoardInfo_T bInfo, size_t y, size_t x, char c);

/* Return this boardinfo's 8 by 8 char array. */
CharBoard BoardInfo_charBoard(BoardInfo_T bInfo);

#endif
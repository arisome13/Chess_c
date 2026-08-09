/*--------------------------------------------------------------------*/
/* move.c                                                             */
/*--------------------------------------------------------------------*/

#include <stdlib.h>
#include "move.h"

struct Move
{
    /* source square */
    Square_T sSrc;

    /* destination square */
    Square_T sDst;
};

Move_T Move_new(Square_T src, Square_T dst) {
    Move_T oMove;

    assert(src != NULL);
    assert(dst != NULL);

    oMove = (Move_T)calloc(1, sizeof(struct Move));
    if (oMove == NULL)
        return NULL;

    oMove->sSrc = src;
    oMove->sDst = dst;

    return oMove;
}
  
/*--------------------------------------------------------------------*/

void Move_free(Move_T oMove) {
    assert(oMove != NULL);
    
    free(oMove->sDst);
    free(oMove->sSrc);
    free(oMove);
}

/*--------------------------------------------------------------------*/

bool Move_equals(Move_T oMove1, Move_T oMove2) {
    assert(oMove1 != NULL);
    assert(oMove2 != NULL);

    return Square_equals(oMove1->sSrc, oMove2->sSrc) 
        && Square_equals(oMove1->sDst, oMove2->sDst);
}

/*--------------------------------------------------------------------*/

char *Move_toString(Move_T oMove) {
    char *src = Square_getNotation(oMove->sSrc);
    char *dst = Square_getNotation(oMove->sDst);
    int iStrRepIndex = 0;
    int iNoteIndex = 0;

    char *pcStrRep = malloc(10);
    if (pcStrRep == NULL)
        return NULL;

    assert(oMove != NULL);

    pcStrRep[iStrRepIndex++] = '\0';
    while (src[iNoteIndex] != '\0') {
        pcStrRep[iStrRepIndex++] = src[iNoteIndex++];
    } iNoteIndex = 0;
    while (dst[iNoteIndex] != '\0') {
        pcStrRep[iStrRepIndex++] = dst[iNoteIndex++];
    } pcStrRep[iStrRepIndex++] = '\0';

    free(src);
    free(dst);
    return pcStrRep;
}


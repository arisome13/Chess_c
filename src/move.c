/*--------------------------------------------------------------------*/
/* move.c                                                             */
/*--------------------------------------------------------------------*/

#include "move.h"

struct Move
{
    /* source square */
    Square_T sSrc;

    /* destination square */
    Square_T sDst;
};

Move_T Move_new(Square_T src, Square_T dst) {
    CHECK_NULL(src);
    CHECK_NULL(dst);

    Move_T oMove = (Move_T)calloc(1, sizeof(struct Move));
    CHECK_MEM(oMove);

    oMove->sSrc = src;
    oMove->sDst = dst;

    return oMove;
}

Move_T Move_read(const char *pcNotation) {
    CHECK_NULL(pcNotation);
    
    Square_T src = Square_newNotation(pcNotation);
    Square_T dst = Square_newNotation(pcNotation + 2);
    
    Move_T oNew = Move_new(src, dst);
    
    return oNew;
}

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

Square_T Move_src(Move_T oMove) {
    return oMove->sSrc;
}
Square_T Move_dst(Move_T oMove) {
    return oMove->sDst;
}

/*--------------------------------------------------------------------*/

char *Move_toString(Move_T oMove) {
    char *src = Square_toString(oMove->sSrc);
    char *dst = Square_toString(oMove->sDst);

    char *pcStrRep = malloc(10);
    CHECK_MEM(pcStrRep);
    
    if (oMove != NULL) 
    {
        pcStrRep[0] = '\0';
        strncpy(pcStrRep, src, 2);
        strncpy(pcStrRep+2, dst, 2);
    }
    else 
    {
        pcStrRep = "NULL";
    }

    free(src);
    free(dst);
    return pcStrRep;
}


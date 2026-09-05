/*--------------------------------------------------------------------*/
/* movepattern.c                                                      */
/*--------------------------------------------------------------------*/

#include "movepattern.h"

struct MoveType
{
    int x, y;
    bool repeating;
};
struct MovePattern
{
    struct MoveType *movetypes[8];
    size_t NUM_MOVETYPES;
};

MovePattern_T MovePattern_new (void) {
    MovePattern_T oPattern = (MovePattern_T)calloc(1, sizeof(struct MovePattern));
    MEM_CHECK(oPattern);

    oPattern->NUM_MOVETYPES = 0;
    
    return oPattern;
}

void MovePattern_free (MovePattern_T oPattern) {
    free(oPattern);
}

void MovePattern_add (MovePattern_T oPattern, int x, int y, bool repeating) {
    MEM_CHECK(oPattern);

    if (oPattern->NUM_MOVETYPES == 8)
        ERROR("Can't have more than 8 move types in a move pattern.");

    // i is the next index available in oPattern
    size_t i = oPattern->NUM_MOVETYPES;

    oPattern->movetypes[i] = (struct MoveType *)malloc(sizeof(struct MoveType));
    oPattern->movetypes[i]->x = x;
    oPattern->movetypes[i]->y = y;
    oPattern->movetypes[i]->repeating = repeating;
}

char *MovePattern_toString (MovePattern_T oPattern) {
    assert(oPattern != NULL);

    char *pcStrRep = malloc(1000);
    if (pcStrRep == NULL)
        return "NO SPACE IN MEMORY";
    
    char *ptr = pcStrRep;

    for (size_t i = 0; i < oPattern->NUM_MOVETYPES; i++) {
        ptr += sprintf(ptr, "(%d, %d) %i\n", 
            oPattern->movetypes[i]->x, oPattern->movetypes[i]->y, oPattern->movetypes[i]->repeating);
    }

    printf("%ld\n", ptr - pcStrRep);
    return pcStrRep;
}


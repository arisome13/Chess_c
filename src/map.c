/*--------------------------------------------------------------------*/
/* map.c                                                             */
/*--------------------------------------------------------------------*/

#include "map.h"
#include "movepattern.h"

struct Map
{
    /* piece map */
    uint64_t ullMap;

    /* piece name */
    char cName;

    /* move pattern */
    MovePattern_T pMoves;
};

/*--------------------------------------------------------------------*/

Map_T Map_new(char name) {
    
    Map_T oMap = (Map_T)calloc(1, sizeof(struct Map));
    MEM_CHECK(oMap);

    oMap->cName = name;
    oMap->ullMap = 0;
    oMap->pMoves = MovePattern_for(oMap->cName);

    return oMap;
}

void Map_free(Map_T oMap) {
    if (oMap != NULL) {
        free(oMap->pMoves);
        free(oMap);
    }
}

Map_T Map_copy (Map_T oMap) {
    assert(oMap != NULL);

    Map_T omCopy = Map_new(oMap->cName);
    omCopy->ullMap = oMap->ullMap;
    
    return omCopy;
}

/*--------------------------------------------------------------------*/

char Map_getName(Map_T oMap) {
    assert(oMap != NULL);
    return oMap->cName;
}

int Map_numPieces(Map_T oMap) {
    assert(oMap != NULL);
    return __builtin_popcountll(oMap->ullMap);
}

uint64_t Map_getPos(Map_T oMap) {
    assert(oMap != NULL);
    return oMap->ullMap;
}

/*--------------------------------------------------------------------*/

void Map_place(Map_T oMap, Square_T oSqr) {
    assert(oMap != NULL);
    oMap->ullMap |= Square_bitMap(oSqr);
}

void Map_capture(Map_T oMap, Square_T oSqr) {
    assert(oMap != NULL);
    oMap->ullMap &= ~Square_bitMap(oSqr);
}

/*--------------------------------------------------------------------*/

bool Map_isCovered(Map_T oMap, int r, int f) {
    assert(oMap != NULL);
    Square_T sqr = Square_newCoords(r, f);
    bool covered = oMap->ullMap >> Square_bitPos(sqr) & 1;
    Square_free(sqr);
    return covered;
}

void Map_addUpPieces (Map_T oMap, int *iTotal) {
    assert(oMap != NULL);
    assert(iTotal != NULL);
    *iTotal += Type_getValue(Map_getName(oMap)) * Map_numPieces(oMap);
}

/*--------------------------------------------------------------------*/

char *Map_toString(Map_T oMap) {
    assert(oMap != NULL);
    
    char *pcStrRep = malloc(700);
    if (pcStrRep == NULL)
        return "NO SPACE IN MEMORY";
    
    char *ptr = pcStrRep;

    ptr += sprintf(ptr, "Piece Type: \'%c\'", oMap->cName);

    for (int r = 0; r <= 7; r++) {
        ptr += sprintf(ptr, 
            "\n  +---+---+---+---+---+---+---+---+\n%d |", 8-r);
        for (int f = 0; f <= 7; f++) {
            char *bit = Map_isCovered(oMap, r, f) ? "X": " ";
            ptr += sprintf(ptr, " %s |", bit);
        }
    }
    ptr += sprintf(ptr, "\n  +---+---+---+---+---+---+---+---+\n");
    ptr += sprintf(ptr, "    a   b   c   d   e   f   g   h  \n");

    return pcStrRep;
}

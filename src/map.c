/*--------------------------------------------------------------------*/
/* map.c                                                             */
/*--------------------------------------------------------------------*/

#include "map.h"
#include "movepattern.h"
#include <ctype.h>

struct Map
{
    /* piece mask */
    Mask_T mask;

    /* piece name */
    char name;

    /* move pattern */
    MovePattern_T moves;
};

/*--------------------------------------------------------------------*/

Map_T Map_new(char name) {
    
    Map_T oMap = (Map_T)calloc(1, sizeof(struct Map));
    CHECK_MEM(oMap);

    oMap->mask = Mask_new();
    oMap->name = name;
    oMap->moves = MovePattern_for(oMap->name);

    return oMap;
}
void Map_free(Map_T oMap) {
    CHECK_NULL(oMap);

    free(oMap->mask);
    free(oMap->moves);
    free(oMap);
}
Map_T Map_copy (Map_T oMap) {
    CHECK_NULL(oMap);

    Map_T omCopy = Map_new(oMap->name); // omCopy->moves is taken care of with Map_new()
    omCopy->mask = Mask_copy(oMap->mask);

    return omCopy;
}

/*--------------------------------------------------------------------*/

char Map_getName(Map_T oMap) {
    CHECK_NULL(oMap);
    return oMap->name;
}
int Map_numPieces(Map_T oMap) {
    CHECK_NULL(oMap);
    return Mask_count(oMap->mask);
}
color Map_color(Map_T oMap) {
    CHECK_NULL(oMap);
    if (isupper(oMap->name))
        return WHITE;
    else
        return BLACK;
}

/*--------------------------------------------------------------------*/

void Map_place(Map_T oMap, Square_T oSqr) {
    CHECK_NULL(oMap);
    Mask_set(oMap->mask, oSqr->x, oSqr->y, true);
}
void Map_remove(Map_T oMap, Square_T oSqr) {
    CHECK_NULL(oMap);
    Mask_set(oMap->mask, oSqr->x, oSqr->y, false);
}

bool Map_isCovered_coords(Map_T oMap, int x, int y) {
    CHECK_NULL(oMap);
    return Mask_isSet(oMap->mask, x, y);
}
bool Map_isCovered_sqr(Map_T oMap, Square_T oSqr) {
    CHECK_NULL(oMap);
    CHECK_NULL(oSqr);
    return Mask_isSet(oMap->mask, oSqr->x, oSqr->y);
}

/*--------------------------------------------------------------------*/

void Map_addUpPieces (Map_T oMap, int *iTotal) {
    CHECK_NULL(oMap);
    CHECK_NULL(iTotal);
    *iTotal += Type_getValue(Map_getName(oMap)) * Map_numPieces(oMap);
}
Mask_T Map_hasRangeTo (Map_T oMap, Move_T oMove) {
    CHECK_NULL(oMap);
    CHECK_NULL(oMove);
    return MovePattern_canMove(oMap->moves, oMove);
}
bool Map_shareSqr (Map_T oMap, Mask_T oMask) {
    CHECK_NULL(oMap);
    CHECK_NULL(oMask);
    return Mask_shareSqr (oMap->mask, oMask);
}

/*--------------------------------------------------------------------*/

char *Map_toString(Map_T oMap) {
    CHECK_NULL(oMap);
    
    char *pcStrRep = malloc(700);
    CHECK_MEM(pcStrRep);
    
    char *ptr = pcStrRep;

    ptr += sprintf(ptr, "Piece Type: \'%c\'", oMap->name);

    for (int r = 0; r <= 7; r++) {
        ptr += sprintf(ptr, 
            "\n  +---+---+---+---+---+---+---+---+\n%d |", 8-r);
        for (int f = 0; f <= 7; f++) {
            char *bit = Map_isCovered_coords(oMap, r, f) ? "X": " ";
            ptr += sprintf(ptr, " %s |", bit);
        }
    }
    ptr += sprintf(ptr, "\n  +---+---+---+---+---+---+---+---+\n");
    ptr += sprintf(ptr, "    a   b   c   d   e   f   g   h  \n");

    return pcStrRep;
}

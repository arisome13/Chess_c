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

    /* define the piece */
    p_type type;
    p_color color;

    /* move pattern */
    MovePattern_T moves;
};

/*--------------------------------------------------------------------*/

Map_T Map_new(char name) {
    
    Map_T oMap = (Map_T)calloc(1, sizeof(struct Map));
    CHECK_MEM(oMap);

    oMap->mask = Mask_new();

    oMap->color = BLACK;
    if ('A' <= name && name <= 'Z') {
        /* switch upper case to lower case */
        name += 32;
        oMap->color = WHITE;
    }

    switch (name)
    {
        case 'p':
            oMap->type = PAWN;
            break;
        case 'n':
            oMap->type = KNIGHT;
            break;
        case 'b':
            oMap->type = BISHOP;
            break;
        case 'r':
            oMap->type = ROOK;
            break;
        case 'q':
            oMap->type = QUEEN;
            break;
        case 'k':
            oMap->type = KING;
            break;
        default:
            printf("Invalid type: %c", name);
            exit(1);
    }

    oMap->moves = MovePattern_for(oMap->type, oMap->color);

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

    Map_T omCopy = (Map_T)calloc(1, sizeof(struct Map));
    CHECK_MEM(omCopy);

    omCopy->mask = Mask_copy(oMap->mask);
    omCopy->color = oMap->color;
    omCopy->type = oMap->type;
    omCopy->moves = MovePattern_for(omCopy->type, omCopy->color);

    return omCopy;
}

/*--------------------------------------------------------------------*/

p_type Map_getType(Map_T oMap) {
    CHECK_NULL(oMap);
    return oMap->type;
}
size_t Map_numPieces(Map_T oMap) {
    CHECK_NULL(oMap);
    return Mask_count(oMap->mask);
}
int map_getPieceValue(Map_T oMap) {
    return Type_getValue(oMap->type, oMap->color);
}
p_color Map_getColor(Map_T oMap) {
    CHECK_NULL(oMap);
    return oMap->color;
}
char Map_getName(Map_T oMap) {
    return Type_toString(oMap->type, oMap->color);
}

/*--------------------------------------------------------------------*/

void Map_place(Map_T oMap, Square_T oSqr) {
    CHECK_NULL(oMap);
    Mask_set(oMap->mask, oSqr->y, oSqr->x, ON);
}
void Map_remove(Map_T oMap, Square_T oSqr) {
    CHECK_NULL(oMap);
    CHECK_NULL(oSqr);
    Mask_set(oMap->mask, oSqr->y, oSqr->x, OFF);
}

bool Map_isCovered_coords(Map_T oMap, size_t y, size_t x) {
    CHECK_NULL(oMap);
    return Mask_isSet(oMap->mask, y, x);
}
bool Map_isCovered_sqr(Map_T oMap, Square_T oSqr) {
    CHECK_NULL(oMap);
    CHECK_NULL(oSqr);
    return Mask_isSet(oMap->mask, oSqr->y, oSqr->x);
}

/*--------------------------------------------------------------------*/

void Map_addUpPieces (Map_T oMap, int *iTotal) {
    CHECK_NULL(oMap);
    CHECK_NULL(iTotal);
    *iTotal += map_getPieceValue(oMap) * Map_numPieces(oMap);
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

    ptr += sprintf(ptr, "Piece Type: \'%c\'", Type_toString(oMap->type, oMap->color));

    for (size_t y = 0; y < 8; y++) {
        ptr += sprintf(ptr, 
            "\n  +---+---+---+---+---+---+---+---+\n%zu |", 8-y);
        for (size_t x = 0; x < 8; x++) {
            char *bit = Map_isCovered_coords(oMap, y, x) ? "X": " ";
            ptr += sprintf(ptr, " %s |", bit);
        }
    }
    ptr += sprintf(ptr, "\n  +---+---+---+---+---+---+---+---+\n");
    ptr += sprintf(ptr, "    a   b   c   d   e   f   g   h  \n");

    return pcStrRep;
}

/*--------------------------------------------------------------------*/
/* movepattern.c                                                      */
/*--------------------------------------------------------------------*/

#include "movepattern.h"

struct MoveType
{
    int dx, dy;
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

void MovePattern_add (MovePattern_T oPattern, int dx, int dy, bool repeating) {
    MEM_CHECK(oPattern);

    if (oPattern->NUM_MOVETYPES == 8)
        ERROR("Can't have more than 8 move types in a move pattern.");

    // i is the next index available in oPattern
    size_t i = oPattern->NUM_MOVETYPES;

    oPattern->movetypes[i] = (struct MoveType *)malloc(sizeof(struct MoveType));
    
    oPattern->movetypes[i]->dx = dx;
    oPattern->movetypes[i]->dy = dy;
    oPattern->movetypes[i]->repeating = repeating;

    oPattern->NUM_MOVETYPES++;
}

MovePattern_T MovePattern_pawn (color c) {
    MovePattern_T mpPiece = MovePattern_new();
    if (c == WHITE) {
        MovePattern_add(mpPiece, 0, -1, false);
        MovePattern_add(mpPiece, 0, -2, false);
    } else {
        MovePattern_add(mpPiece, 0, 1, false);
        MovePattern_add(mpPiece, 0, 2, false);
    }
    return mpPiece;
}
MovePattern_T MovePattern_knight (void) {
    MovePattern_T mpPiece = MovePattern_new();
    MovePattern_add(mpPiece, 1, 2, false);
    MovePattern_add(mpPiece, 1, -2, false);
    MovePattern_add(mpPiece, -1, 2, false);
    MovePattern_add(mpPiece, -1, -2, false);
    MovePattern_add(mpPiece, 2, 1, false);
    MovePattern_add(mpPiece, -2, 1, false);
    MovePattern_add(mpPiece, 2, -1, false);
    MovePattern_add(mpPiece, -2, -1, false);
    return mpPiece;
}
MovePattern_T MovePattern_bishop (void) {
    MovePattern_T mpPiece = MovePattern_new();
    MovePattern_add(mpPiece, 1, 1, true);
    MovePattern_add(mpPiece, 1, -1, true);
    MovePattern_add(mpPiece, -1, 1, true);
    MovePattern_add(mpPiece, -1, -1, true);
    return mpPiece;
}
MovePattern_T MovePattern_rook (void) {
    MovePattern_T mpPiece = MovePattern_new();
    MovePattern_add(mpPiece, 1, 0, true);
    MovePattern_add(mpPiece, 0, 1, true);
    MovePattern_add(mpPiece, -1, 0, true);
    MovePattern_add(mpPiece, 0, -1, true);
    return mpPiece;
}
MovePattern_T MovePattern_queen (void) {
    MovePattern_T mpPiece = MovePattern_new();
    MovePattern_add(mpPiece, 1, 0, true);
    MovePattern_add(mpPiece, 0, 1, true);
    MovePattern_add(mpPiece, -1, 0, true);
    MovePattern_add(mpPiece, 0, -1, true);
    MovePattern_add(mpPiece, 1, 1, true);
    MovePattern_add(mpPiece, 1, -1, true);
    MovePattern_add(mpPiece, -1, 1, true);
    MovePattern_add(mpPiece, -1, -1, true);
    return mpPiece;
}
MovePattern_T MovePattern_king (void) {
    MovePattern_T mpPiece = MovePattern_new();
    MovePattern_add(mpPiece, 1, 0, false);
    MovePattern_add(mpPiece, 0, 1, false);
    MovePattern_add(mpPiece, -1, 0, false);
    MovePattern_add(mpPiece, 0, -1, false);
    MovePattern_add(mpPiece, 1, 1, false);
    MovePattern_add(mpPiece, 1, -1, false);
    MovePattern_add(mpPiece, -1, 1, false);
    MovePattern_add(mpPiece, -1, -1, false);
    return mpPiece;
}
MovePattern_T MovePattern_for (char pieceName) {
    if (pieceName == 'p')
        return MovePattern_pawn(BLACK);
    else if (pieceName == 'P')
        return MovePattern_pawn(WHITE);
    else if (pieceName == 'n' || pieceName == 'N')
        return MovePattern_knight();
    else if (pieceName == 'b' || pieceName == 'B')
        return MovePattern_bishop();
    else if (pieceName == 'r' || pieceName == 'R')
        return MovePattern_rook();
    else if (pieceName == 'q' || pieceName == 'Q')
        return MovePattern_queen();
    else if (pieceName == 'k' || pieceName == 'K')
        return MovePattern_king();
    else {
        ERROR("Invalid piece \'%s\'. Should implement its move pattern.", pieceName);
        return NULL;
    }
}

char *MovePattern_toString (MovePattern_T oPattern) {
    assert(oPattern != NULL);

    char *pcStrRep = malloc(200);
    if (pcStrRep == NULL)
        return "NO SPACE IN MEMORY";
    
    char *ptr = pcStrRep;

    for (size_t i = 0; i < oPattern->NUM_MOVETYPES; i++) {
        ptr += sprintf(ptr, "(%d, %d) ", 
            oPattern->movetypes[i]->dx, oPattern->movetypes[i]->dy);
        if (oPattern->movetypes[i]->repeating)
            ptr += sprintf(ptr, ": repeats ");
        ptr += sprintf(ptr, "\n");
    }

    printf("%ld\n", ptr - pcStrRep);
    return pcStrRep;
}


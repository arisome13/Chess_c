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
    CHECK_MEM(oPattern);

    oPattern->NUM_MOVETYPES = 0;
    
    return oPattern;
}
void MovePattern_free (MovePattern_T oPattern) {
    free(oPattern);
}
MovePattern_T MovePattern_copy (MovePattern_T oPattern) {
    MovePattern_T opCopy = MovePattern_new();

    for (int i = 0; i < 8; i++) {
        if (oPattern->movetypes[i] == NULL) {
            break;
        }
        MovePattern_add(opCopy, oPattern->movetypes[i]->dx, 
            oPattern->movetypes[i]->dy, oPattern->movetypes[i]->repeating);
    }
    
    return opCopy;
}

void MovePattern_add (MovePattern_T oPattern, int dx, int dy, bool repeating) {
    CHECK_MEM(oPattern);

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

MovePattern_T movepattern_pawn (color c) {
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
MovePattern_T movepattern_knight (void) {
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
MovePattern_T movepattern_bishop (void) {
    MovePattern_T mpPiece = MovePattern_new();
    MovePattern_add(mpPiece, 1, 1, true);
    MovePattern_add(mpPiece, 1, -1, true);
    MovePattern_add(mpPiece, -1, 1, true);
    MovePattern_add(mpPiece, -1, -1, true);
    return mpPiece;
}
MovePattern_T movepattern_rook (void) {
    MovePattern_T mpPiece = MovePattern_new();
    MovePattern_add(mpPiece, 1, 0, true);
    MovePattern_add(mpPiece, 0, 1, true);
    MovePattern_add(mpPiece, -1, 0, true);
    MovePattern_add(mpPiece, 0, -1, true);
    return mpPiece;
}
MovePattern_T movepattern_queen (void) {
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
MovePattern_T movepattern_king (void) {
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
        return movepattern_pawn(BLACK);
    else if (pieceName == 'P')
        return movepattern_pawn(WHITE);
    else if (pieceName == 'n' || pieceName == 'N')
        return movepattern_knight();
    else if (pieceName == 'b' || pieceName == 'B')
        return movepattern_bishop();
    else if (pieceName == 'r' || pieceName == 'R')
        return movepattern_rook();
    else if (pieceName == 'q' || pieceName == 'Q')
        return movepattern_queen();
    else if (pieceName == 'k' || pieceName == 'K')
        return movepattern_king();
    else {
        ERROR("Invalid piece \'%s\'. Should implement its move pattern.", pieceName);
        return NULL;
    }
}

Mask_T MovePattern_canMove (MovePattern_T oPattern, Move_T oMove) {
    printf("Make sure to TEST THIS FUNCTION");

    int dx = Move_dst(oMove)->x - Move_src(oMove)->x;
    int dy = Move_dst(oMove)->y - Move_src(oMove)->y;

    Mask_T traversedSqrs = Mask_new();
    for (size_t i = 0; i < oPattern->NUM_MOVETYPES; i++) 
    {
        if (dx == oPattern->movetypes[i]->dx && dy == oPattern->movetypes[i]->dy)
            return Mask_new();
        
        if (!oPattern->movetypes[i]->repeating)
            continue;
        
        // if the direction of movement is the same...
        if (oPattern->movetypes[i]->dy/oPattern->movetypes[i]->dx == dy/dx)
        {
            Mask_reset(traversedSqrs);
            
            // check if one can move like the other
            for (int j = 1; j < 8; j++) 
            {
                if (dx == j * oPattern->movetypes[i]->dx && dy == j * oPattern->movetypes[i]->dy)
                    return traversedSqrs;

                Mask_set(traversedSqrs, Move_src(oMove)->x + j * oPattern->movetypes[i]->dx, Move_src(oMove)->y + j * oPattern->movetypes[i]->dy, ON);
            }
        }
    }
    free(traversedSqrs);
    return NULL;
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


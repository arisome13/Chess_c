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
        MovePattern_add(opCopy, oPattern->movetypes[i]->dy, 
            oPattern->movetypes[i]->dx, oPattern->movetypes[i]->repeating);
    }
    
    return opCopy;
}

void MovePattern_add (MovePattern_T oPattern, int dy, int dx, bool repeating) {
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

MovePattern_T movepattern_pawn (p_color c) {
    MovePattern_T mpPiece = MovePattern_new();
    if (c == WHITE) {
        MovePattern_add(mpPiece, -1, 0, false);
        MovePattern_add(mpPiece, -2, 0, false);
    } else {
        MovePattern_add(mpPiece, 1, 0, false);
        MovePattern_add(mpPiece, 2, 0, false);
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

MovePattern_T MovePattern_for (p_type type, p_color color) {
    if (type == PAWN)
        return movepattern_pawn(color);
    else if (type == KNIGHT)
        return movepattern_knight();
    else if (type == BISHOP)
        return movepattern_bishop();
    else if (type == ROOK)
        return movepattern_rook();
    else if (type == QUEEN)
        return movepattern_queen();
    else if (type == KING)
        return movepattern_king();
    else {
        ERROR("Invalid piece type(%d), color(%d). Should implement its move pattern.", type, color);
        return NULL;
    }
}

Mask_T MovePattern_canMove (MovePattern_T oPattern, Move_T oMove) {
    CHECK_NULL(oPattern);
    CHECK_NULL(oMove);

    int dx = (int)Move_dst(oMove)->x - (int)Move_src(oMove)->x;
    int dy = (int)Move_dst(oMove)->y - (int)Move_src(oMove)->y;

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
            for (int j = 2; j < 8; j++) 
            {
                if (dx == j * oPattern->movetypes[i]->dx && dy == j * oPattern->movetypes[i]->dy)
                    return traversedSqrs;

                int tempX = Move_src(oMove)->x + j * oPattern->movetypes[i]->dx;
                int tempY = Move_src(oMove)->y + j * oPattern->movetypes[i]->dy;
                if (!(0 <= tempX && tempX < 8 && 0 <= tempY && tempY < 8))
                    break;
                
                Mask_set(traversedSqrs, tempY, tempX, ON);
            }
        }
    }
    free(traversedSqrs);
    return NULL;
}

char *MovePattern_toString (MovePattern_T oPattern) {
    CHECK_NULL(oPattern);

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

    return pcStrRep;
}
char *MovePattern_showMovesFrom (MovePattern_T oPattern, Square_T oSqr) {
    CHECK_NULL(oPattern);

    char *pcStrRep = malloc(800);
    CHECK_MEM(pcStrRep);
    char *ptr = pcStrRep;

    ptr += sprintf(ptr, "  +---+---+---+---+---+---+---+---+\n");

    Move_T move = Move_new(oSqr, Square_newCoords(0, 0));
    for (Move_dst(move)->y = 0; Move_dst(move)->y <= 7; Move_dst(move)->y++) {
        ptr += sprintf(ptr, "%zu |", 8-Move_dst(move)->y);
        for (Move_dst(move)->x = 0; Move_dst(move)->x <= 7; Move_dst(move)->x++) {
            char bit = ' ';
            if (Square_equals(Move_dst(move), Move_src(move)))
                bit = 'o';
            else if (MovePattern_canMove(oPattern, move))
                bit = 'X';
            ptr += sprintf(ptr, " %c |", bit);
        }
        ptr += sprintf(ptr, "\n  +---+---+---+---+---+---+---+---+\n");
    }
    ptr += sprintf(ptr, "    a   b   c   d   e   f   g   h  ");

    return pcStrRep;
}


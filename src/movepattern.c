/*--------------------------------------------------------------------*/
/* movepattern.c                                                      */
/*--------------------------------------------------------------------*/

#include "movepattern.h"

struct MovePattern
{
    struct Movement *movements[MAX_MOVE_TYPES];
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
        struct Movement *mnt = MovePattern_getMovement(oPattern, i);
        if (mnt == NULL) break;
        MovePattern_add(opCopy, mnt->dy, mnt->dx, mnt->num_reps, mnt->end);
    }
    
    return opCopy;
}

void MovePattern_add (MovePattern_T oPattern, int dy, int dx, 
        size_t reps, CaptureRule end) {
    CHECK_MEM(oPattern);

    if (oPattern->NUM_MOVETYPES == 8)
        ERROR("Can't have more than 8 move types in a move pattern.");

    // i is the next index available in oPattern
    size_t i = oPattern->NUM_MOVETYPES;

    oPattern->movements[i] = (struct Movement *)malloc(sizeof(struct Movement));
    
    oPattern->movements[i]->dx = dx;
    oPattern->movements[i]->dy = dy;
    oPattern->movements[i]->num_reps = reps;
    oPattern->movements[i]->end = end;

    oPattern->NUM_MOVETYPES++;
}

MovePattern_T movepattern_pawn (p_color c) {
    MovePattern_T mpPiece = MovePattern_new();
    if (c == WHITE) {
        MovePattern_add(mpPiece, -1, 0, 2, CANT_CAPTURE);
        MovePattern_add(mpPiece, -1, 1, 1, ONLY_CAPTURE);
        MovePattern_add(mpPiece, -1, -1, 1, ONLY_CAPTURE);
    } else {
        MovePattern_add(mpPiece, 1, 0, 2, CANT_CAPTURE);
        MovePattern_add(mpPiece, 1, 1, 1, ONLY_CAPTURE);
        MovePattern_add(mpPiece, 1, -1, 1, ONLY_CAPTURE);
    }
    return mpPiece;
}
MovePattern_T movepattern_knight (void) {
    MovePattern_T mpPiece = MovePattern_new();
    MovePattern_add(mpPiece, 1, 2, 1, BOTH);
    MovePattern_add(mpPiece, 1, -2, 1, BOTH);
    MovePattern_add(mpPiece, -1, 2, 1, BOTH);
    MovePattern_add(mpPiece, -1, -2, 1, BOTH);
    MovePattern_add(mpPiece, 2, 1, 1, BOTH);
    MovePattern_add(mpPiece, -2, 1, 1, BOTH);
    MovePattern_add(mpPiece, 2, -1, 1, BOTH);
    MovePattern_add(mpPiece, -2, -1, 1, BOTH);
    return mpPiece;
}
MovePattern_T movepattern_bishop (void) {
    MovePattern_T mpPiece = MovePattern_new();
    MovePattern_add(mpPiece, 1, 1, 0, BOTH);
    MovePattern_add(mpPiece, 1, -1, 0, BOTH);
    MovePattern_add(mpPiece, -1, 1, 0, BOTH);
    MovePattern_add(mpPiece, -1, -1, 0, BOTH);
    return mpPiece;
}
MovePattern_T movepattern_rook (void) {
    MovePattern_T mpPiece = MovePattern_new();
    MovePattern_add(mpPiece, 1, 0, 0, BOTH);
    MovePattern_add(mpPiece, 0, 1, 0, BOTH);
    MovePattern_add(mpPiece, -1, 0, 0, BOTH);
    MovePattern_add(mpPiece, 0, -1, 0, BOTH);
    return mpPiece;
}
MovePattern_T movepattern_queen (void) {
    MovePattern_T mpPiece = MovePattern_new();
    MovePattern_add(mpPiece, 1, 0, 0, BOTH);
    MovePattern_add(mpPiece, 0, 1, 0, BOTH);
    MovePattern_add(mpPiece, -1, 0, 0, BOTH);
    MovePattern_add(mpPiece, 0, -1, 0, BOTH);
    MovePattern_add(mpPiece, 1, 1, 0, BOTH);
    MovePattern_add(mpPiece, 1, -1, 0, BOTH);
    MovePattern_add(mpPiece, -1, 1, 0, BOTH);
    MovePattern_add(mpPiece, -1, -1, 0, BOTH);
    return mpPiece;
}
MovePattern_T movepattern_king (void) {
    MovePattern_T mpPiece = MovePattern_new();
    MovePattern_add(mpPiece, 1, 0, 1, BOTH);
    MovePattern_add(mpPiece, 0, 1, 1, BOTH);
    MovePattern_add(mpPiece, -1, 0, 1, BOTH);
    MovePattern_add(mpPiece, 0, -1, 1, BOTH);
    MovePattern_add(mpPiece, 1, 1, 1, BOTH);
    MovePattern_add(mpPiece, 1, -1, 1, BOTH);
    MovePattern_add(mpPiece, -1, 1, 1, BOTH);
    MovePattern_add(mpPiece, -1, -1, 1, BOTH);
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

Mask_T MovePattern_canMove (MovePattern_T oPattern, Move_T oMove, bool isCapture) {
    CHECK_NULL(oPattern);
    CHECK_NULL(oMove);

    int dx = (int)Move_dst(oMove)->x - (int)Move_src(oMove)->x;
    int dy = (int)Move_dst(oMove)->y - (int)Move_src(oMove)->y;

    Mask_T traversedSqrs = Mask_new();
    for (size_t i = 0; i < oPattern->NUM_MOVETYPES; i++) 
    {
        // get the movement struct
        struct Movement *mtype = MovePattern_getMovement(oPattern, i);
        
        // check if there is a mismatch between the capture rule and whether this move captures
        if ((isCapture && mtype->end == CANT_CAPTURE) 
            || (!isCapture && mtype->end == ONLY_CAPTURE))
            continue;

        // if the movement matches the move, return that it crosses no squares
        if (dx == mtype->dx && dy == mtype->dy)
            return traversedSqrs;
        
        // if the movement can't repeat more than once, 
        // it can't follow through with this move 
        if (mtype->num_reps == 1)
            continue;
        
        // if the movement along one axis is zero and the move 
        // being tested moves along that axis, invalid
        if (mtype->dx * dx == 0 && (dx != 0 || mtype->dx != 0)) continue;
        if (mtype->dy * dy == 0 && (dy != 0 || mtype->dy != 0)) continue;

        // if the movement along one axis is opposit from the tested move's
        // direction along that axis, invalid
        if (mtype->dx * dx < 0 || mtype->dy * dy < 0) continue;
        
        Mask_reset(traversedSqrs);

        // get the maximum number of times this move can repeat
        int max_reps = mtype->num_reps == 0 ? 8 : mtype->num_reps;
        assert(0 <= max_reps && max_reps <= 8);
        
        // check if one can move like the other
        for (int j = 1; j < max_reps; j++) 
        {
            if (dx == j * mtype->dx && dy == j * mtype->dy)
                return traversedSqrs;

            int tempX = Move_src(oMove)->x + j * mtype->dx;
            int tempY = Move_src(oMove)->y + j * mtype->dy;
            if (!(0 <= tempX && tempX < 8 && 0 <= tempY && tempY < 8))
                break;
            
            Mask_set(traversedSqrs, tempY, tempX, ON);
        }
    }

    free(traversedSqrs);
    return NULL;
}

struct Movement *MovePattern_getMovement(MovePattern_T oPattern, int i) {
    return oPattern->movements[i];
}

char *MovePattern_toString (MovePattern_T oPattern) {
    CHECK_NULL(oPattern);

    char *pcStrRep = malloc(200);
    if (pcStrRep == NULL)
        return "NO SPACE IN MEMORY";
    
    char *ptr = pcStrRep;

    for (size_t i = 0; i < oPattern->NUM_MOVETYPES; i++)
    {
        struct Movement *mnt = MovePattern_getMovement(oPattern, i);
        ptr += sprintf(ptr, "(%d, %d) ", mnt->dx, mnt->dy);
        
        if (mnt->num_reps != 1)
            ptr += sprintf(ptr, ": repeats ");
        else if (mnt->num_reps != 0)
            ptr += sprintf(ptr, " (%zu) ", mnt->num_reps);

        if (mnt->end == CANT_CAPTURE)
            ptr += sprintf(ptr, ": can't capture ");
        else if (mnt->end == ONLY_CAPTURE)
            ptr += sprintf(ptr, ": only captures ");
        
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
                bit = '~';
            else if (MovePattern_canMove(oPattern, move, true))
                bit = 'X';
            else if (MovePattern_canMove(oPattern, move, false))
                bit = 'O';
            ptr += sprintf(ptr, " %c |", bit);
        }
        ptr += sprintf(ptr, "\n  +---+---+---+---+---+---+---+---+\n");
    }
    ptr += sprintf(ptr, "    a   b   c   d   e   f   g   h  ");

    return pcStrRep;
}


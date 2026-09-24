/*--------------------------------------------------------------------*/
/* validation.c                                                       */
/*--------------------------------------------------------------------*/

#include "validation.h"

void Validate_chessboard(ChessBoard_T oBoard) {
    CHECK_NULL(oBoard);
    printf("Not implemented yet: Validate_chessboard");
}

/* return true if dxy is within (-8, 8) */
bool is_valid_dxy (int dxy)
{
    return -8 < dxy && dxy < 8;
}
/* return true if xy is within [0, 8) */
bool is_valid_xy (size_t xy)
{
    return 0 <= xy && xy < 8;
}
/* used for: */
bool Validate_src_dyx (Square_T src, int dy, int dx) {
    CHECK_NULL(src);
    
    if (!is_valid_xy(src->y) || !is_valid_xy(src->x))
        return false;

    if (!is_valid_dxy(dy) || !is_valid_dxy(dx))
        return false;

    int dstY = src->y + dy; int dstX = src->x + dx;

    return is_valid_xy(dstY) && is_valid_xy(dstX);
}

bool Validate_move (Move_T move) {
    Square_T src = Move_src(move);
    Square_T dst = Move_dst(move);
    if (src->x == dst->x && src->y == dst->y)
        return false;
    else
        return true;
}

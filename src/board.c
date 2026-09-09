/*--------------------------------------------------------------------*/
/* board.c                                                            */
/*--------------------------------------------------------------------*/

#include "board.h"
#include "parameters.h"
#include "validation.h"
#include <mask.h>

enum {MAX_PIECE_TYPES = 64};

struct ChessBoard
{
    /* the collections of different piece types */
    Map_T pmPieceMaps[MAX_PIECE_TYPES];

    /* the number of non-null maps */
    size_t NUM_MAPS;
};

/*--------------------------------------------------------------------*/

ChessBoard_T ChessBoard_new(const char *pcFen)
{
    CHECK_NULL(pcFen);

    ChessBoard_T oBoard = (ChessBoard_T)calloc(1, sizeof(struct ChessBoard));
    CHECK_MEM(oBoard);
    
    ChessBoard_setFen(oBoard, pcFen);
    
    return oBoard;
}
void ChessBoard_free(ChessBoard_T oBoard)
{
    CHECK_NULL(oBoard);

    for (size_t m = 0; m < oBoard->NUM_MAPS; m++)
        Map_free(oBoard->pmPieceMaps[m]);

    free(oBoard);
}
ChessBoard_T ChessBoard_copy(ChessBoard_T oBoard) {
    CHECK_NULL(oBoard);
    
    ChessBoard_T obCopy = (ChessBoard_T)calloc(1, sizeof(struct ChessBoard));
    CHECK_MEM(obCopy);
    
    for (size_t m = 0; m < oBoard->NUM_MAPS; m++) {
        obCopy->pmPieceMaps[m] = Map_copy(oBoard->pmPieceMaps[m]);
    }
    
    return obCopy;
}

/*--------------------------------------------------------------------*/

/* Return the map from oBoard matching cName. Create a new one if one
   hasn't already been created. */
Map_T chessboard_getOrMakeMap(ChessBoard_T oBoard, p_type type) {
    CHECK_NULL(oBoard);
    for (size_t m = 0; m < oBoard->NUM_MAPS; m++) {
        if (Map_getType(oBoard->pmPieceMaps[m]) == type)
            return oBoard->pmPieceMaps[m];
    }
    if (oBoard->NUM_MAPS == MAX_PIECE_TYPES)
        ERROR("ChessBoard does not have the piece requested and not space for more.");
    
    oBoard->pmPieceMaps[oBoard->NUM_MAPS] = Map_new(type);
    Map_T madeMap = oBoard->pmPieceMaps[oBoard->NUM_MAPS];
    oBoard->NUM_MAPS++;
    return madeMap;
}
/* USED FOR setFen */

void ChessBoard_setFen(ChessBoard_T oBoard, const char *pcFen)
{
    CHECK_NULL(pcFen);
    CHECK_NULL(oBoard);

    oBoard->NUM_MAPS = 0;
    Square_T sqr = Square_newCoords(0, 0);

    int i = 0;
    char c = pcFen[i++];
    Map_T pMap;
    while (c != '\0')
    {
        switch (c)
        {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                sqr->x += c - '0';
                break;
            case '/':
                assert(sqr->x == 8);
                sqr->x = 0;
                sqr->y++;
                break;
            case ' ': 
                /* finished reading pcFen */
                goto finishedParsing;
            default:
                pMap = chessboard_getOrMakeMap(oBoard, c);
                
                /* place the piece */
                Map_place(pMap, sqr);

                /* index to the next column on the board */
                sqr->x++;
        }
        c = pcFen[i++];
    }
    finishedParsing:
    
    free(sqr);
}

/* Return the map from oBoard that has a piece on oSqr. Return NULL if 
   none like that exist. */
Map_T chessboard_getMapFromSqr(ChessBoard_T oBoard, Square_T oSqr) {
    CHECK_NULL(oBoard);
    //Validate_chessboard(oBoard);
    for (size_t m = 0; m < oBoard->NUM_MAPS; m++) {
        if (Map_isCovered_sqr(oBoard->pmPieceMaps[m], oSqr))
            return oBoard->pmPieceMaps[m];
    }
    return NULL;
}
/* Returns SUCCESS if move could be completed, some other move result 
    otherwise and leaves the chessboard untouched. */
r_move chessboard_handleMove(ChessBoard_T oBoard, Move_T oMove) 
{
    // get the map that contains the piece on the src square
    Map_T srcMap = chessboard_getMapFromSqr(oBoard, Move_src(oMove));
    
    // if there is no piece on the src square for the move, the move is INVALID
    if (srcMap == NULL)
        return NO_PIECE_ON_SRC;

    // if the piece does not have the range to get the the dst square, the move is INVALID
    Mask_T traversed = Map_hasRangeTo(srcMap, oMove);
    if (traversed == NULL)
        return DOESNT_HAVE_RANGE;

    // if the piece traverses squares that are covered, the move is INVALID
    for (size_t m = 0; m < oBoard->NUM_MAPS; m++) {
        if (Map_shareSqr(oBoard->pmPieceMaps[m], traversed))
            return BLOCKED_PATH;
    }
    
    // get the map that contains the piece on the dst square
    Map_T dstMap = chessboard_getMapFromSqr(oBoard, Move_dst(oMove));
    
    // if there is a piece on the dst square...
    if (dstMap != NULL)
    {
        // if the piece is the same color as the moving piece, the move is INVALID
        if (Map_getColor(dstMap) == Map_getColor(srcMap))
            return SAME_COLOR_DST;
        
        Map_remove(dstMap, Move_dst(oMove));
    }
    
    Map_remove(srcMap, Move_src(oMove));
    Map_place(srcMap, Move_dst(oMove));
    return SUCCESS;
}
/* USED FOR tryMove */

r_move ChessBoard_tryMove(ChessBoard_T oBoard, Move_T oMove)
{
    /* currently configured as a king capture game */
    
    r_move result = chessboard_handleMove(oBoard, oMove);
    
    if (result != SUCCESS)
        /* try the move as a special move */;
    
    return result;

}

/*--------------------------------------------------------------------*/

p_type ChessBoard_typeOnSqr(ChessBoard_T oBoard, Square_T oSqr) {
    CHECK_NULL(oBoard);
    CHECK_NULL(oSqr);
    for (size_t m = 0; m < oBoard->NUM_MAPS; m++) {
        if (Map_isCovered_sqr(oBoard->pmPieceMaps[m], oSqr))
            return Map_getType(oBoard->pmPieceMaps[m]);
    }
    return NO_TYPE;
}
p_color ChessBoard_colorOnSqr(ChessBoard_T oBoard, Square_T oSqr) {
    CHECK_NULL(oBoard);
    CHECK_NULL(oSqr);
    for (size_t m = 0; m < oBoard->NUM_MAPS; m++) {
        if (Map_isCovered_sqr(oBoard->pmPieceMaps[m], oSqr))
            return Map_getColor(oBoard->pmPieceMaps[m]);
    }
    return NO_COLOR;
}

void ChessBoard_onEachMap(ChessBoard_T oBoard, MapFunction func, int *data) {
    assert(oBoard != NULL);
    assert(func != NULL);

    for (size_t m = 0; m < oBoard->NUM_MAPS; m++)
        func(oBoard->pmPieceMaps[m], data);
}

/*--------------------------------------------------------------------*/

char *ChessBoard_toString(ChessBoard_T oBoard)
{
    CHECK_NULL(oBoard);

    char *pcStrRep = malloc(800);
    CHECK_MEM(pcStrRep);
    char *ptr = pcStrRep;

    ptr += sprintf(ptr, "  +---+---+---+---+---+---+---+---+\n");

    for (size_t y = 0; y < 8; y++) {
        ptr += sprintf(ptr, "%zu |", 8-y);
        for (size_t x = 0; x < 8; x++) {
            char bit = ' ';
            // go through all the bit maps
            for (size_t m = 0; m < oBoard->NUM_MAPS; m++) {
                if (Map_isCovered_coords(oBoard->pmPieceMaps[m], y, x)) {
                    bit = Map_getName(oBoard->pmPieceMaps[m]);
                    break;
                }
            }
            ptr += sprintf(ptr, " %c |", bit);
        }
        ptr += sprintf(ptr, "\n  +---+---+---+---+---+---+---+---+\n");
    }
    ptr += sprintf(ptr, "    a   b   c   d   e   f   g   h  ");

    return pcStrRep;
}


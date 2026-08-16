/*--------------------------------------------------------------------*/
/* board.c                                                            */
/*--------------------------------------------------------------------*/

#include "board.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

enum {NUM_PLAYERS = 2, PIECE_TYPES = 6};

struct ChessBoard
{
    /* the collection of different pieces: 2 players, 6 piece types. 
        The enums type and color can be used to index through these
        piece masks: color 0-1, type: 0-5 */
    Mask_T mPieceMasks[NUM_PLAYERS][PIECE_TYPES];
};

ChessBoard_T ChessBoard_new(const char *pcFen) {
    ChessBoard_T oBoard;

    assert(pcFen != NULL);

    oBoard = (ChessBoard_T)calloc(1, sizeof(struct ChessBoard));
    if (oBoard == NULL)
        return oBoard;

    /* initialize piece masks */
    oBoard->mPieceMasks[BLACK][PAWN] = Mask_new("p");
    if (oBoard->mPieceMasks[BLACK][PAWN] == NULL) return NULL;
    oBoard->mPieceMasks[BLACK][ROOK] = Mask_new("r");
    if (oBoard->mPieceMasks[BLACK][ROOK] == NULL) return NULL;
    oBoard->mPieceMasks[BLACK][KNIGHT] = Mask_new("n");
    if (oBoard->mPieceMasks[BLACK][KNIGHT] == NULL) return NULL;
    oBoard->mPieceMasks[BLACK][BISHOP] = Mask_new("b");
    if (oBoard->mPieceMasks[BLACK][BISHOP] == NULL) return NULL;
    oBoard->mPieceMasks[BLACK][QUEEN] = Mask_new("q");
    if (oBoard->mPieceMasks[BLACK][QUEEN] == NULL) return NULL;
    oBoard->mPieceMasks[BLACK][KING] = Mask_new("k");
    if (oBoard->mPieceMasks[BLACK][KING] == NULL) return NULL;
    oBoard->mPieceMasks[WHITE][PAWN] = Mask_new("P");
    if (oBoard->mPieceMasks[WHITE][PAWN] == NULL) return NULL;
    oBoard->mPieceMasks[WHITE][ROOK] = Mask_new("R");
    if (oBoard->mPieceMasks[WHITE][ROOK] == NULL) return NULL;
    oBoard->mPieceMasks[WHITE][KNIGHT] = Mask_new("N");
    if (oBoard->mPieceMasks[WHITE][KNIGHT] == NULL) return NULL;
    oBoard->mPieceMasks[WHITE][BISHOP] = Mask_new("B");
    if (oBoard->mPieceMasks[WHITE][BISHOP] == NULL) return NULL;
    oBoard->mPieceMasks[WHITE][QUEEN] = Mask_new("Q");
    if (oBoard->mPieceMasks[WHITE][QUEEN] == NULL) return NULL;
    oBoard->mPieceMasks[WHITE][KING] = Mask_new("K");
    if (oBoard->mPieceMasks[WHITE][KING] == NULL) return NULL;
    
    Square_T sqr = Square_newCoords(0, 0);
    if (sqr == NULL) return NULL;

    /* place black back rank pieces */
    sqr->iRank = 0;
    sqr->iFile = 0;
    Mask_place(oBoard->mPieceMasks[BLACK][ROOK], sqr);
    sqr->iFile++;
    Mask_place(oBoard->mPieceMasks[BLACK][KNIGHT], sqr);
    sqr->iFile++;
    Mask_place(oBoard->mPieceMasks[BLACK][BISHOP], sqr);
    sqr->iFile++;
    Mask_place(oBoard->mPieceMasks[BLACK][QUEEN], sqr);
    sqr->iFile++;
    Mask_place(oBoard->mPieceMasks[BLACK][KING], sqr);
    sqr->iFile++;
    Mask_place(oBoard->mPieceMasks[BLACK][BISHOP], sqr);
    sqr->iFile++;
    Mask_place(oBoard->mPieceMasks[BLACK][KNIGHT], sqr);
    sqr->iFile++;
    Mask_place(oBoard->mPieceMasks[BLACK][ROOK], sqr);
    
    /* place black pawns */
    sqr->iRank = 1;
    for (sqr->iFile = 0; sqr->iFile < 8; sqr->iFile++) {
        Mask_place(oBoard->mPieceMasks[BLACK][PAWN], sqr);
    }
    /* place white pawns */
    sqr->iRank = 6;
    for (sqr->iFile = 0; sqr->iFile < 8; sqr->iFile++) {
        Mask_place(oBoard->mPieceMasks[WHITE][PAWN], sqr);
    }
    /* place white back rank pieces */
    sqr->iRank = 7;
    sqr->iFile = 0;
    Mask_place(oBoard->mPieceMasks[WHITE][ROOK], sqr);
    sqr->iFile++;
    Mask_place(oBoard->mPieceMasks[WHITE][KNIGHT], sqr);
    sqr->iFile++;
    Mask_place(oBoard->mPieceMasks[WHITE][BISHOP], sqr);
    sqr->iFile++;
    Mask_place(oBoard->mPieceMasks[WHITE][QUEEN], sqr);
    sqr->iFile++;
    Mask_place(oBoard->mPieceMasks[WHITE][KING], sqr);
    sqr->iFile++;
    Mask_place(oBoard->mPieceMasks[WHITE][BISHOP], sqr);
    sqr->iFile++;
    Mask_place(oBoard->mPieceMasks[WHITE][KNIGHT], sqr);
    sqr->iFile++;
    Mask_place(oBoard->mPieceMasks[WHITE][ROOK], sqr);

    free(sqr);
    return oBoard;
}

void ChessBoard_free(ChessBoard_T oBoard) {
    assert(oBoard != NULL);

    for (int c = 0; c < NUM_PLAYERS; c++)
        for (int p = 0; p < PIECE_TYPES; p++)
            Mask_free(oBoard->mPieceMasks[c][p]);

    free(oBoard);
}

char *ChessBoard_toString(ChessBoard_T oBoard) {
    assert(oBoard != NULL);

    char *pcStrRep = malloc(800);
    if (pcStrRep == NULL)
        return "NO SPACE IN MEMORY";
    char *ptr = pcStrRep;

    ptr += sprintf(ptr, "Chess Board:");

    for (int r = 0; r <= 7; r++) {
        ptr += sprintf(ptr, "\n  +---+---+---+---+---+---+---+---+\n%d |", 8-r);
        for (int f = 0; f <= 7; f++) {
            char *bit = " ";
            // go through all the bit masks
            for (int c = 0; c < NUM_PLAYERS; c++) {
                for (int p = 0; p < PIECE_TYPES; p++) {
                    if (Mask_isCovered(oBoard->mPieceMasks[c][p], r, f)) {
                        if (strcmp(bit, " ") == 0) {
                            bit = oBoard->mPieceMasks[c][p]->cpName;
                        } else {
                            assert(1 == 0);
                        }
                        goto foundPiece;
                    }
                }
            }
            foundPiece:
            ptr += sprintf(ptr, " %.1s |", bit);
        }
    }
    ptr += sprintf(ptr, "\n  +---+---+---+---+---+---+---+---+\n");
    ptr += sprintf(ptr, "    a   b   c   d   e   f   g   h  \n");

    return pcStrRep;
}


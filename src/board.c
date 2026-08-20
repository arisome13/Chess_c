/*--------------------------------------------------------------------*/
/* board.c                                                            */
/*--------------------------------------------------------------------*/

#include "board.h"
#include "parameters.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

enum {MAX_PIECE_TYPES = 64};
const char *STARTING_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

struct ChessBoard
{
    /* the collections of different piece types */
    Mask_T pmPieceMasks[MAX_PIECE_TYPES];
};

/*--------------------------------------------------------------------*/

ChessBoard_T ChessBoard_new(const char *pcFen) 
{
    ChessBoard_T oBoard = (ChessBoard_T)calloc(1, sizeof(struct ChessBoard));
    MEM_CHECK(oBoard);
    
    if (pcFen == NULL)
        ChessBoard_setFen(oBoard, STARTING_FEN);
    else
        ChessBoard_setFen(oBoard, pcFen);
    
    return oBoard;
}

void ChessBoard_free(ChessBoard_T oBoard)
{
    assert(oBoard != NULL);

    for (int m = 0; m < MAX_PIECE_TYPES; m++)
        Mask_free(oBoard->pmPieceMasks[m]);

    free(oBoard);
}

ChessBoard_T ChessBoard_copy(ChessBoard_T oBoard) {
    assert(oBoard != NULL);
    
    ChessBoard_T obCopy = (ChessBoard_T)calloc(1, sizeof(struct ChessBoard));
    MEM_CHECK(obCopy);
    
    for (int m = 0; m < MAX_PIECE_TYPES; m++) {
        if (obCopy->pmPieceMasks[m] != NULL)
            obCopy->pmPieceMasks[m] = Mask_copy(oBoard->pmPieceMasks[m]);
        else
            break;
    }
    
    return obCopy;
}

/*--------------------------------------------------------------------*/

void ChessBoard_setFen(ChessBoard_T oBoard, const char *pcFen)
{
    /* reset the bit boards */
    for (int m = 0; m < MAX_PIECE_TYPES; m++) {
        Mask_free(oBoard->pmPieceMasks[m]);
        oBoard->pmPieceMasks[m] = NULL;
    }

    Square_T sqr = Square_newCoords(0, 0);
    MEM_CHECK(sqr);

    int i = 0;
    char c = pcFen[i++];
    Mask_T tempMask;
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
                sqr->iFile += c - '0';
                break;
            case '/':
                assert(sqr->iFile == 8);
                sqr->iFile = 0;
                sqr->iRank++;
                break;
            case ' ': 
                /* finished reading pcFen */
                goto finishedParsing;
            default:
                tempMask = ChessBoard_getMask(oBoard, c);

                /* no 'c' pieces on the board just yet */
                if (tempMask == NULL)
                    tempMask = Mask_new(c);
                
                /* place the piece */
                Mask_place(tempMask, sqr);

                /* index to the next column on the board */
                sqr->iFile++;
        }
        c = pcFen[i++];
    }
    finishedParsing:
    
    free(sqr);
}

Mask_T ChessBoard_getMask(ChessBoard_T oBoard, char cName) {
    for (int m = 0; m < MAX_PIECE_TYPES; m++) {
        if (oBoard->pmPieceMasks[m] == NULL)
            return oBoard->pmPieceMasks[m];
        else if (Mask_getName(oBoard->pmPieceMasks[m]) == cName)
            return oBoard->pmPieceMasks[m];
    }
    ERROR("ChessBoard does not have the piece requested and not space for more.");
    return NULL;
}

void ChessBoard_onEachMask(ChessBoard_T oBoard, MaskFunction func, int *data) {
    assert(oBoard != NULL);
    assert(func != NULL);

    for (int m = 0; m < MAX_PIECE_TYPES; m++) {
        if (oBoard->pmPieceMasks[m] != NULL)
            func(oBoard->pmPieceMasks[m], data);
    }
}

/*--------------------------------------------------------------------*/

char *ChessBoard_toString(ChessBoard_T oBoard)
{
    assert(oBoard != NULL);

    char *pcStrRep = malloc(800);
    if (pcStrRep == NULL)
        return "NO SPACE IN MEMORY";
    char *ptr = pcStrRep;

    ptr += sprintf(ptr, "  +---+---+---+---+---+---+---+---+\n");

    for (int r = 0; r <= 7; r++) {
        ptr += sprintf(ptr, "%d |", 8-r);
        for (int f = 0; f <= 7; f++) {
            char bit = ' ';
            // go through all the bit masks
            for (int m = 0; m < MAX_PIECE_TYPES; m++) {
                if (Mask_isCovered(oBoard->pmPieceMasks[m], r, f)) {
                    if (bit == ' ') {
                        bit = Mask_getName(oBoard->pmPieceMasks[m]);
                    } else {
                        ERROR("Multiple pieces at the same location.");
                    }
                    goto foundPiece;
                }
            }
            foundPiece:
            ptr += sprintf(ptr, " %c |", bit);
        }
        ptr += sprintf(ptr, "\n  +---+---+---+---+---+---+---+---+\n");
    }
    ptr += sprintf(ptr, "    a   b   c   d   e   f   g   h  \n");

    return pcStrRep;
}


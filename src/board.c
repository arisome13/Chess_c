/*--------------------------------------------------------------------*/
/* board.c                                                            */
/*--------------------------------------------------------------------*/

#include "board.h"
#include "parameters.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

enum {MAX_PIECE_TYPES = 64};

struct ChessBoard
{
    /* the collections of different piece types */
    Map_T pmPieceMaps[MAX_PIECE_TYPES];
};

/*--------------------------------------------------------------------*/

ChessBoard_T ChessBoard_new(const char *pcFen) 
{
    assert(pcFen != NULL);

    ChessBoard_T oBoard = (ChessBoard_T)calloc(1, sizeof(struct ChessBoard));
    MEM_CHECK(oBoard);
    
    ChessBoard_setFen(oBoard, pcFen);
    
    return oBoard;
}

void ChessBoard_free(ChessBoard_T oBoard)
{
    assert(oBoard != NULL);

    for (int m = 0; m < MAX_PIECE_TYPES; m++)
        Map_free(oBoard->pmPieceMaps[m]);

    free(oBoard);
}

ChessBoard_T ChessBoard_copy(ChessBoard_T oBoard) {
    assert(oBoard != NULL);
    
    ChessBoard_T obCopy = (ChessBoard_T)calloc(1, sizeof(struct ChessBoard));
    MEM_CHECK(obCopy);
    
    for (int m = 0; m < MAX_PIECE_TYPES; m++) {
        if (obCopy->pmPieceMaps[m] != NULL)
            obCopy->pmPieceMaps[m] = Map_copy(oBoard->pmPieceMaps[m]);
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
        Map_free(oBoard->pmPieceMaps[m]);
        oBoard->pmPieceMaps[m] = NULL;
    }

    Square_T sqr = Square_newCoords(0, 0);
    MEM_CHECK(sqr);

    int i = 0;
    char c = pcFen[i++];
    Map_T tempMap;
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
                tempMap = ChessBoard_getMap(oBoard, c);

                /* no 'c' pieces on the board just yet */
                if (tempMap == NULL)
                    tempMap = Map_new(c);
                
                /* place the piece */
                Map_place(tempMap, sqr);

                /* index to the next column on the board */
                sqr->iFile++;
        }
        c = pcFen[i++];
    }
    finishedParsing:
    
    free(sqr);
}

Map_T ChessBoard_getMap(ChessBoard_T oBoard, char cName) {
    for (int m = 0; m < MAX_PIECE_TYPES; m++) {
        if (oBoard->pmPieceMaps[m] == NULL) {
            oBoard->pmPieceMaps[m] = Map_new(cName);
            return oBoard->pmPieceMaps[m];
        }
        else if (Map_getName(oBoard->pmPieceMaps[m]) == cName)
            return oBoard->pmPieceMaps[m];
    }
    ERROR("ChessBoard does not have the piece requested and not space for more.");
    return NULL;
}

void ChessBoard_onEachMap(ChessBoard_T oBoard, MapFunction func, int *data) {
    assert(oBoard != NULL);
    assert(func != NULL);

    for (int m = 0; m < MAX_PIECE_TYPES; m++) {
        if (oBoard->pmPieceMaps[m] != NULL)
            func(oBoard->pmPieceMaps[m], data);
    }
}

r_move ChessBoard_tryMove(ChessBoard_T oBoard, Move_T oMove) {
    return FAIL;
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
            // go through all the bit maps
            for (int m = 0; m < MAX_PIECE_TYPES; m++) {
                if (oBoard->pmPieceMaps[m] == NULL)
                    break;
                if (Map_isCovered(oBoard->pmPieceMaps[m], r, f)) {
                    if (bit == ' ') {
                        bit = Map_getName(oBoard->pmPieceMaps[m]);
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
    ptr += sprintf(ptr, "    a   b   c   d   e   f   g   h  ");

    return pcStrRep;
}


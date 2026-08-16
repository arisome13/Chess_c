/*--------------------------------------------------------------------*/
/* square.c                                                           */
/*--------------------------------------------------------------------*/

#include "square.h"
#include <stdio.h>
#include <assert.h>

Square_T Square_initCoords(int rank, int file) {
    Square_T oSqr;

    assert(0 <= rank && rank < 8 && 0 <= file && file < 8);

    oSqr = (Square_T)calloc(1, sizeof(struct Square));
    if (oSqr == NULL)
        return NULL;

    oSqr->iFile = file;
    oSqr->iRank = rank;

    return oSqr;
}

Square_T Square_initNotation(char *pcNotation) {
    int r;
    int f;

    assert(pcNotation != NULL);

    f = pcNotation[0] - 'a';
    r = pcNotation[1] - '1';

    return Square_initCoords(r, f);
}
  
/*--------------------------------------------------------------------*/

void Square_free(Square_T oSquare) {
    assert(oSquare != NULL);
    free(oSquare);
}

/*--------------------------------------------------------------------*/

bool Square_equals(Square_T oSquare1, Square_T oSquare2) {
    return oSquare1->iFile == oSquare2->iFile && oSquare1->iRank == oSquare2->iRank;
}

int Square_bitPos(Square_T oSquare) {
    return (oSquare->iFile + (oSquare->iRank * 8)) >> 1;
}

uint64_t Square_bitMask(Square_T oSquare) {
    return 1 << Square_bitPos(oSquare);
}

char *Square_getNotation(Square_T oSquare) {
    char *pcNotation = (char *)malloc(3);
    if (pcNotation == NULL) return NULL;

    if (oSquare == NULL) 
    {
        pcNotation[0] = '-';
        pcNotation[1] = '\0';
    
        return pcNotation;
    }
    else
    {
        pcNotation[0] = 'a' + oSquare->iFile;
        pcNotation[1] = '1' + oSquare->iRank;
        pcNotation[2] = '\0';

        return pcNotation;
    }
}

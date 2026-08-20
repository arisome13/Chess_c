/*--------------------------------------------------------------------*/
/* square.c                                                           */
/*--------------------------------------------------------------------*/

#include "square.h"
#include <assert.h>

Square_T Square_newCoords(int rank, int file) {
    Square_T oSqr;

    assert(0 <= rank && rank < 8 && 0 <= file && file < 8);

    oSqr = (Square_T)calloc(1, sizeof(struct Square));
    MEM_CHECK(oSqr);

    oSqr->iRank = rank;
    oSqr->iFile = file;

    return oSqr;
}

Square_T Square_newNotation(char *pcNotation) {
    int r;
    int f;

    assert(pcNotation != NULL);

    f = pcNotation[0] - 'a';
    r = pcNotation[1] - '1';

    return Square_newCoords(7 - r, f);
}
  
void Square_free(Square_T oSquare) {
    assert(oSquare != NULL);
    free(oSquare);
}

Square_T Square_copy(Square_T oSquare) {
    assert(oSquare != NULL);
    return Square_newCoords(oSquare->iRank, oSquare->iFile);
}

/*--------------------------------------------------------------------*/

bool Square_equals(Square_T oSquare1, Square_T oSquare2) {
    assert(oSquare1 != NULL);
    assert(oSquare2 != NULL);
    return oSquare1->iFile == oSquare2->iFile && oSquare1->iRank == oSquare2->iRank;
}

int Square_bitPos(Square_T oSquare) {
    assert(oSquare != NULL);
    return oSquare->iFile + ((7 - oSquare->iRank) * 8);
}

uint64_t Square_bitMask(Square_T oSquare) {
    assert(oSquare != NULL);
    return 1ULL << Square_bitPos(oSquare);
}

/*--------------------------------------------------------------------*/

char *Square_toString(Square_T oSquare) {
    assert(oSquare != NULL);
    
    char *pcNotation = (char *)malloc(3);
    MEM_CHECK(pcNotation);

    if (oSquare == NULL)
    {
        pcNotation[0] = '-';
        pcNotation[1] = '\0';
    
        return pcNotation;
    }
    else
    {
        pcNotation[0] = 'a' + oSquare->iFile;
        pcNotation[1] = '1' + 7 - oSquare->iRank;
        pcNotation[2] = '\0';

        return pcNotation;
    }
}

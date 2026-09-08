/*--------------------------------------------------------------------*/
/* square.c                                                           */
/*--------------------------------------------------------------------*/

#include "square.h"

Square_T Square_newCoords(size_t y, size_t x) {
    Square_T oSqr;

    CHECK_COORDS(y, x, "Square_newCoords");

    oSqr = (Square_T)calloc(1, sizeof(struct Square));
    CHECK_MEM(oSqr);

    oSqr->x = x;
    oSqr->y = y;

    return oSqr;
}

Square_T Square_newNotation(const char *pcNotation) {
    CHECK_NULL(pcNotation);

    size_t x = pcNotation[0] - 'a';
    size_t y = 7 - (pcNotation[1] - '1');

    return Square_newCoords(y, x);
}
  
void Square_free(Square_T oSquare) {
    CHECK_NULL(oSquare);
    free(oSquare);
}

Square_T Square_copy(Square_T oSquare) {
    CHECK_NULL(oSquare);
    return Square_newCoords(oSquare->y, oSquare->x);
}

/*--------------------------------------------------------------------*/

bool Square_equals(Square_T oSquare1, Square_T oSquare2) {
    CHECK_NULL(oSquare1);
    CHECK_NULL(oSquare2);
    return oSquare1->y == oSquare2->y && oSquare1->x == oSquare2->x;
}

/*--------------------------------------------------------------------*/

char *Square_toString(Square_T oSquare){
    char *pcNotation = (char *)malloc(3);
    CHECK_MEM(pcNotation);

    if (oSquare == NULL)
    {
        pcNotation[0] = '-';
        pcNotation[1] = '\0';
    }
    else
    {
        pcNotation[0] = 'a' + oSquare->x;
        pcNotation[1] = '8' - oSquare->y;
        pcNotation[2] = '\0';
    }
    return pcNotation;
}

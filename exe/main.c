
#include "engine.h"

int main(void)
{
    char *tempStr;

    // create the engine
    Engine_T eng = Engine_new(NULL);
    tempStr = Engine_toString(eng);
    printf("%s\n", tempStr);
    free(tempStr);

    Move_T aMoves[256];
    size_t len = Engine_legalMoves(eng, aMoves);
    printf("num available moves for white: %zu\n", len);

    for (size_t i = 0; i < len; i++) {
        char *strmove = Move_toString(aMoves[i]);
        printf("Move #%zu: %s\n", i, strmove);
        Move_free(aMoves[i]);
        free(strmove);
    }

    /*
    // find the best move
    Move_T bestM = Engine_bestMove(eng);
    tempStr = Move_toString(bestM);
    printf("\nBest move: %s\n", tempStr);
    free(tempStr);
    */

    /*
    r_move result = Engine_makeMove(eng, bestM);
    Move_free(bestM);

    PRINT("%s\n\n", MoveResult_toString(result));
    tempStr = Engine_toString(eng);
    printf("%s\n", tempStr);
    free(tempStr);
    */

    Engine_free(eng);
}


#include "engine.h"

int main(void)
{
    char *tempStr;

    // create the engine
    Engine_T eng = Engine_new(NULL);
    tempStr = Engine_toString(eng);
    printf("%s\n", tempStr);
    free(tempStr);

    MoveArray_T aMoves = Engine_legalMoves(eng);
    char *strarr = MoveArray_toString(aMoves);
    printf("%s\n", strarr);
    free(strarr);

    /*
    // find the best move
    Move_T bestM = Engine_bestMove(eng);
    tempStr = Move_toString(bestM);
    printf("\nBest move: %s\n", tempStr);
    free(tempStr);
    */

    /*
    s_move result = Engine_makeMove(eng, bestM);
    Move_free(bestM);

    PRINT("%s\n\n", MoveState_toString(result));
    tempStr = Engine_toString(eng);
    printf("%s\n", tempStr);
    free(tempStr);
    */

    Engine_free(eng);
}


#include "engine.h"

int main(void)
{
    char *tempStr;

    // create the engine
    Engine_T eng = Engine_new(NULL);
    tempStr = Engine_toString(eng);
    printf("%s\n", tempStr);
    free(tempStr);

    // find the best move
    Move_T bestM = Engine_bestMove(eng);
    tempStr = Move_toString(bestM);
    printf("\nBest move: %s\n", tempStr);
    free(tempStr);

    r_move result = Engine_makeMove(eng, bestM);
    PRINT("%s\n\n", MoveResult_toString(result));
    tempStr = Engine_toString(eng);
    printf("%s\n", tempStr);
    free(tempStr);

    Move_free(bestM);
    Engine_free(eng);
}

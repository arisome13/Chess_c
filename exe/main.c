
#include "engine.h"

int main(void)
{
    // create the engine
    Engine_T eng = Engine_new(NULL);
    printf("%s\n", Engine_toString(eng));

    // find the best move
    Move_T bestM = Engine_bestMove(eng);
    printf("\nBest move: %s\n", Move_toString(bestM));

    Engine_makeMove(eng, bestM);
    printf("%s\n", Engine_toString(eng));

    Move_free(bestM);
    Engine_free(eng);
}

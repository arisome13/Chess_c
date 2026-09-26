
#include <stdio.h>
#include "engine.h"
#include "board.h"

int main (void) {
    char *tempStr;

    const char *fen = "4N3/3K4/p1p1bP1P/1Q2n3/7p/Brp1P1rp/1P3P1n/1kN5 b - - 0 1";

    // create the engine
    Engine_T eng = Engine_new(fen);
    tempStr = Engine_toString(eng);
    printf("%s\n", tempStr);
    free(tempStr);

    Move_T legalMoves[256];
    size_t moveListSize = Engine_legalMoves(eng, legalMoves);
    PRINT("Moves list contians %zu moves:\n", moveListSize);
    for (size_t i = 0; i < moveListSize; i++) {
        if (i != 0)
            PRINT(", ");
        char *movestr = Engine_notation(eng, legalMoves[i]);
        PRINT("%s", movestr);
        free(movestr);
    }

    /*
    // find the best move
    Eval_T engEval = Engine_evaluate(eng);
    tempStr = Eval_toString(engEval);
    printf("\nEval: %s\n", tempStr);
    free(tempStr);
    Eval_free(engEval);
    */

    Engine_free(eng);
}
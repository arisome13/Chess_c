
#include <stdio.h>
#include "engine.h"

int main (void) {
    char *tempStr;

    // create the engine
    Engine_T eng = Engine_new("r1bq1rk1/pp2bppp/2np1n2/2p1p3/2P1P3/2NP1N2/PP2BPPP/R1BQ1RK1 w - - 4 9");
    tempStr = Engine_toString(eng);
    printf("%s\n", tempStr);
    free(tempStr);

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
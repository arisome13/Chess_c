
#include <stdio.h>
#include "engine.h"

int main (void) {
    char *tempStr;

    // create the engine
    Engine_T eng = Engine_new(NULL);
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
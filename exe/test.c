
#include <stdio.h>
#include "engine.h"
#include "board.h"

int main (void) {
    char *tempStr;

    const char *fen = "r1bqkbnr/ppp2ppp/4p3/4n3/8/5N2/PPP1PPPP/RNBQKB1R w KQkq - 0 1";

    // create the engine
    Engine_T eng = Engine_new(fen);
    tempStr = Engine_toString(eng);
    printf("%s\n", tempStr);
    free(tempStr);

    // find the best move
    /*Move_T bm = Engine_bestMove(eng);
    tempStr = Move_toString(bm);
    printf("\nEval: %s\n", tempStr);
    free(tempStr);
    Move_free(bm);*/

    Engine_free(eng);
}

#include <stdio.h>
#include "engine.h"
#include "board.h"

int main (void)
{
    const char *fen = "r1bqkbnr/ppp2ppp/4p3/4n3/8/5N2/PPP1PPPP/RNBQKB1R w KQkq - 0 1";
    const char *moveStr = "d1d8";
    char *tempStr;

    // create the engine
    Engine_T eng = Engine_new(fen);

    // print the enging
    tempStr = Engine_toString(eng);
    printf("%s\n", tempStr);
    free(tempStr);

    // make a move
    Move_T move = Move_read(moveStr);
    Engine_makeMove(eng, move);
    
    // print the engine
    tempStr = Engine_toString(eng);
    printf("%s\n", tempStr);
    free(tempStr);

    // undo the move
    Engine_undo(eng);

    // print the engine
    tempStr = Engine_toString(eng);
    printf("%s\n", tempStr);
    free(tempStr);
    
    // free the relevant pointers
    Move_free(move);
    Engine_free(eng);
}
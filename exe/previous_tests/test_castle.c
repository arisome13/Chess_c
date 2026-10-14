
#include <stdio.h>
#include "engine.h"
#include "board.h"

int main (void)
{
    //const char *fen = "r1bqkbnr/ppp2ppp/4p3/4n3/8/5N2/PPP1PPPP/RNBQKB1R w KQkq - 0 1";
    Engine_T eng;
    MoveArray_T omArray;
    s_move result;

    // enter the moves to test an enpassant capture
    omArray = MoveArray_new();
    MoveArray_add(omArray, Move_read("e2e4"));
    MoveArray_add(omArray, Move_read("a7a6"));
    MoveArray_add(omArray, Move_read("f1d3"));
    MoveArray_add(omArray, Move_read("a6a5"));
    MoveArray_add(omArray, Move_read("g1e2"));
    MoveArray_add(omArray, Move_read("a5a4"));
    MoveArray_add(omArray, Move_read("e1g1"));
    MoveArray_add(omArray, Move_read("a8a7"));

    // create the engine with starting position
    eng = Engine_new(NULL);
    Engine_PRINT(eng); // print the position and eval

    for (size_t i = 0; i < MoveArray_length(omArray); i++)
    {
        result = Engine_makeMove(eng, MoveArray_get(omArray, i));
        PRINT("Result was %s\n", MoveState_toString(result));
        Engine_PRINT(eng);
        if (result != SUCCESS)
            break;
    }
    
    // free the relevant pointers
    Engine_free(eng);
    MoveArray_free(omArray);
}
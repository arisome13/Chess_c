
#include "engine.h"

const char *STARTING_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

int main(void)
{
    // create the engine
    Engine_T eng = Engine_new(STARTING_FEN);

    // print out what board the engine holds
    printf("%s", Engine_toString(eng));
    
    // free the engine
    Engine_free(eng);
}

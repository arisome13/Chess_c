
#include "engine.h"

int main(void)
{
    // create the engine
    Engine_T eng = Engine_new(STARTING_FEN);

    // print out what board the engine holds
    printf("%s", Engine_toString(eng));
    
    // free the engine
    Engine_free(eng);
}

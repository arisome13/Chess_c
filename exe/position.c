
/* 
 * Website: https://www.muxgen.com/gaming-tools/chess-position-generator
 * A great way to create random positions!
*/

#include <stdio.h>
#include "board.h"

int main (void) {
    char *tempStr;

    // create the engine
    ChessBoard_T b = ChessBoard_new("8/2k5/2p2p2/3p1P2/3P2K1/2P1N3/8/8 w - - 1 48");
    tempStr = ChessBoard_toString(b);
    printf("%s\n", tempStr);
    free(tempStr);
   
    ChessBoard_free(b);
}
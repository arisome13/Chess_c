
#include "engine.h"
#include <results.h>

int main(void)
{
    char *tempStr;

    // create the engine
    Engine_T eng = Engine_new(NULL);
    tempStr = Engine_toString(eng);
    printf("%s\n", tempStr);
    free(tempStr);

    char *usrStr = malloc(6);
    size_t moves = 0;
    while (moves < 10) 
    {
        printf("Enter a move: ");
        fgets(usrStr, 6, stdin);
        // Remove newline if present
        if (usrStr[strlen(usrStr) - 1] == '\n') {
            usrStr[strlen(usrStr) - 1] = '\0';
        }

        Move_T usrMove = Move_read(usrStr);
        r_move moveResult = Engine_makeMove(eng, usrMove);
        if (moveResult != SUCCESS)    
            ERROR("Invalid move for reason: %s\n", MoveResult_toString(moveResult));
        else
            PRINT("Succeeded in moving.\n");

        tempStr = Engine_toString(eng);
        printf("%s\n", tempStr);
        free(tempStr);
        moves++;
    }

    free(usrStr);
    Engine_free(eng);
    
    return 0;
}

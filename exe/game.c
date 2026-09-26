
#include "engine.h"

int main(void)
{
    char *tempStr;

    // create the engine
    Engine_T eng = Engine_new(NULL);
    tempStr = Engine_toString(eng);
    printf("\n%s\n", tempStr);
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
        {
            PRINT("Invalid move for reason: %s\n", MoveResult_toString(moveResult));
        }
        else
        {
            tempStr = Engine_toString(eng);
            PRINT("Succeeded in moving.\n\n%s\n", tempStr);
            free(tempStr);

            PRINT("Engine's turn now...\n");
            Move_T bestMove = Engine_bestMove(eng);
            r_move r = Engine_makeMove(eng, bestMove);
            assert(r == SUCCESS);

            char*movestr = Move_toString(bestMove);
            tempStr = Engine_toString(eng);
            PRINT("Engine moved %s.\n\n%s\n", movestr, tempStr);
            free(tempStr);
            free(movestr);
            moves++;
        }
    }

    free(usrStr);
    Engine_free(eng);
    
    return 0;
}

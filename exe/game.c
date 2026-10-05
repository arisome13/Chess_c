
#include "engine.h"

int main(void)
{
    char *tempStr;
    size_t MAX_MOVES = 100;

    // create the engine
    Engine_T eng = Engine_new(NULL);
    tempStr = Engine_toString(eng);
    printf("\n%s\n", tempStr);
    free(tempStr);

    char *usrStr = malloc(6);
    size_t moves = 0;
    while (moves < MAX_MOVES)
    {
        printf("Enter a move (4 letters): ");
        fgets(usrStr, 6, stdin);
        // Remove newline if present
        if (usrStr[strlen(usrStr) - 1] == '\n') {
            usrStr[strlen(usrStr) - 1] = '\0';
        }

        if (strncmp(usrStr, "exit", 4) == 0)
        {
            PRINT("\nExiting the chess engine program. \nThank you for playing.\n\n");
            break;
        }

        Move_T usrMove = Move_read(usrStr);
        s_move moveResult = Engine_makeMove(eng, usrMove);
        if (moveResult != SUCCESS)
        {
            PRINT("Invalid move for reason: %s\n", MoveState_toString(moveResult));
        }
        else
        {
            tempStr = Engine_toString(eng);
            PRINT("Succeeded in moving.\n\n%s\n", tempStr);
            free(tempStr);

            PRINT("Engine's turn now...\n");
            Move_T bestMove = Engine_bestMove(eng);
            s_move r = Engine_makeMove(eng, bestMove);
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


#include "engine.h"

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
        Engine_makeMove(eng, usrMove);

        tempStr = Engine_toString(eng);
        printf("%s\n", tempStr);
        free(tempStr);
        moves++;
    }

    free(usrStr);
    Engine_free(eng);
    
    return 0;
}

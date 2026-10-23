
#include "userint.h"
#include "engine.h"
#include "boardinfo.h"

Engine_T eng;

void Upon_Move_fromUI(size_t fromY, size_t fromX, size_t toY, size_t toX)
{
    CHECK_MEM(eng);
    Move_T move;
    s_move result;

    // make user move
    move = Move_new(Square_newCoords(fromY, fromX), Square_newCoords(toY, toX));
    result = Engine_makeMove(eng, move);
    Move_free(move);

    if (result == SUCCESS) {
        BoardInfo_T bi = Engine_getInfo(eng);
        ChessUI_load(BoardInfo_charBoard(bi));
        BoardInfo_free(bi);
    } else {
        ERROR("Invalid user move.\n");
    }

    // loat and make the best engine move
    move = Engine_bestMove(eng);
    result = Engine_makeMove(eng, move);
    Move_free(move);

    if (result == SUCCESS) {
        BoardInfo_T bi = Engine_getInfo(eng);
        ChessUI_load(BoardInfo_charBoard(bi));
        BoardInfo_free(bi);
    } else {
        ERROR("Invalid engine move.\n");
    }
}
void Display_Destroyed(void) {
    Engine_free(eng);
}

int main (void)
{
    eng = Engine_new(NULL);
    ChessUI_run(Upon_Move_fromUI, Display_Destroyed);
}
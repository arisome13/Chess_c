
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
        PRINT("Invalid user move.\n");
        return;
    }

    // loat and make the best engine move
    move = Engine_bestMove(eng);
    if (move == NULL) {
        PRINT("No best move found.\n");
        return;
    }
    result = Engine_makeMove(eng, move);
    Move_free(move);

    if (result == SUCCESS) {
        BoardInfo_T bi = Engine_getInfo(eng);
        ChessUI_load(BoardInfo_charBoard(bi));
        BoardInfo_free(bi);
    } else {
        PRINT("Invalid engine move.\n");
        return;
    }
}

int main (void)
{
    eng = Engine_new(NULL);
    ChessUI_run(Upon_Move_fromUI);
    // after the gui is done
    Engine_free(eng);
}

#include <glib.h>
#include "userint.h"
#include "engine.h"
#include "boardinfo.h"

// chess engine
static Engine_T eng;
// search thread
static GThread *searcher = NULL;
// 1 indicates that the engine is thinking
static bool thinking = false;

static void refresh_ui(Move_T recentMove)
{
    Square_T src = NULL;
    Square_T dst = NULL;
    if (recentMove != NULL) {
        src = Move_src(recentMove);
        dst = Move_dst(recentMove);
    }

    BoardInfo_T bi = Engine_getInfo(eng);
    ChessUI_load(BoardInfo_charBoard(bi), src, dst);
    BoardInfo_free(bi);
}

static gboolean apply_engine_move(gpointer data)
{
    Move_T move = (Move_T)data;

    /* the searcher has returned (or is about to), so this join is short */
    if (searcher != NULL) {
        g_thread_join(searcher);
        searcher = NULL;
    }

    if (move != NULL) {
        s_move result = Engine_makeMove(eng, move);

        if (result == SUCCESS)
            refresh_ui(move);
        else
            PRINT("Invalid engine move.\n");

        Move_free(move);
    } else {
        PRINT("No best move found.\n");
    }

    thinking = false;
    return G_SOURCE_REMOVE;   /* run once */
}
static gpointer search_thread(gpointer unused)
{
    (void)unused;
    Move_T best = Engine_bestMove(eng);
    g_idle_add(apply_engine_move, best);   /* hand the result to GTK */
    return NULL;
}

void Upon_Move_fromUI(size_t fromY, size_t fromX, size_t toY, size_t toX)
{
    CHECK_MEM(eng);
    Move_T move;
    s_move result;

    // ignore clicks while the engine is thinking
    if (thinking)
        return;

    // make user move
    move = Move_new(Square_newCoords(fromY, fromX), Square_newCoords(toY, toX));
    result = Engine_makeMove(eng, move);

    if (result != SUCCESS) {
        PRINT("Invalid user move.\n");
        return;
    }
    refresh_ui(move);
    Move_free(move);

    // start the engine's search on the searcher thread
    thinking = true;
    searcher = g_thread_new("engine", search_thread, NULL);
}

int main (void)
{
    eng = Engine_new(NULL);
    ChessUI_run(Upon_Move_fromUI);
    // window is closed...
    
    // close the searching thread
    if (searcher != NULL) {
        g_thread_join(searcher);
        searcher = NULL;
    }
    // free the engine
    Engine_free(eng);
}
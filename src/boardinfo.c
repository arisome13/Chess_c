
#include "boardinfo.h"

struct BoardInfo
{
    char charboard[8][8];
};

BoardInfo_T BoardInfo_new(void)
{
    BoardInfo_T bInfo = (BoardInfo_T)malloc(1 * sizeof(struct BoardInfo));
    CHECK_MEM(bInfo);

    for (size_t y = 0; y < 8; y++) {
    for (size_t x = 0; x < 8; x++) {
        bInfo->charboard[y][x] = 0;
    }}
    
    return bInfo;
}

void BoardInfo_free(BoardInfo_T bInfo)
{
    free(bInfo);
}

char BoardInfo_get(BoardInfo_T bInfo, size_t y, size_t x)
{
    CHECK_NULL(bInfo);
    return bInfo->charboard[y][x];
}

void BoardInfo_set(BoardInfo_T bInfo, size_t y, size_t x, char c)
{
    CHECK_NULL(bInfo);
    bInfo->charboard[y][x] = c;
}

CharBoard BoardInfo_charBoard(BoardInfo_T bInfo)
{
    CHECK_MEM(bInfo);
    return bInfo->charboard;
}

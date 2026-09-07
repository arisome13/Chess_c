/*--------------------------------------------------------------------*/
/* mask.c                                                             */
/*--------------------------------------------------------------------*/

#include "mask.h"

struct Mask
{
    u_int64_t ullMask;
};

Mask_T Mask_new(void) 
{
    Mask_T oMask = (Mask_T)calloc(1, sizeof(struct Mask));
    CHECK_MEM(oMask);

    oMask->ullMask = 0;

    return oMask;
}
void Mask_free(Mask_T oMask)
{
    CHECK_NULL(oMask);
    free(oMask);
}
Mask_T Mask_copy (Mask_T oMask)
{
    CHECK_NULL(oMask);

    Mask_T mCopy = Mask_new();
    CHECK_MEM(mCopy);
    
    mCopy->ullMask = oMask->ullMask;

    return mCopy;
}
void Mask_reset (Mask_T oMask)
{
    CHECK_NULL(oMask);
    oMask->ullMask = 0;
}

/*--------------------------------------------------------------------*/

size_t Mask_count(Mask_T oMask)
{
    CHECK_NULL(oMask);
    return __builtin_popcountll(oMask->ullMask);
}
bool Mask_isSet(Mask_T oMask, size_t x, size_t y)
{
    CHECK_NULL(oMask);
    CHECK_COORDS(x, y);
    return (oMask->ullMask >> (8 * y + x)) & 1;
}
bool Mask_shareSqr(Mask_T oMask1, Mask_T oMask2) {
    CHECK_NULL(oMask1);
    CHECK_NULL(oMask2);
    return (oMask1->ullMask & oMask2->ullMask) != 0;
}

/*--------------------------------------------------------------------*/

void Mask_set(Mask_T oMask, size_t x, size_t y, enum ON_OFF ONorOFF) {
    CHECK_NULL(oMask);
    CHECK_COORDS(x, y);
    if (ONorOFF == ON)
        oMask->ullMask |= 1ULL << (8 * y + x);
    else
        oMask->ullMask &= ~(1ULL << (8 * y + x));
}

/*--------------------------------------------------------------------*/

char *Mask_toString(Mask_T oMask) {
    CHECK_NULL(oMask);
    
    char *pcStrRep = malloc(700);
    CHECK_MEM(pcStrRep);
    
    char *ptr = pcStrRep;

    for (int y = 0; y < 8; y++) {
        ptr += sprintf(ptr, 
            "\n  +---+---+---+---+---+---+---+---+\n%d |", 8-y);
        for (int x = 0; x < 8; x++) {
            char *bit = Mask_isSet(oMask, x, y) ? "X": " ";
            ptr += sprintf(ptr, " %s |", bit);
        }
    }
    ptr += sprintf(ptr, "\n  +---+---+---+---+---+---+---+---+\n");

    return pcStrRep;
}


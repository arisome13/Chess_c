/*--------------------------------------------------------------------*/
/* mask.c                                                             */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stdio.h>
#include "mask.h"
#include "string.h"
#include "square.h"

Mask_T Mask_new(char *name) {
    Mask_T oMask;

    assert(name != NULL);

    oMask = (Mask_T)calloc(1, sizeof(struct Mask));
    if (oMask == NULL)
        return NULL;

    oMask->cpName = name;
    oMask->ullMask = 0;

    return oMask;
}
  
void Mask_free(Mask_T oMask) {
    if (oMask != NULL)
        free(oMask);
}

/*--------------------------------------------------------------------*/

bool Mask_matchesName(Mask_T oMask, char *name) {
    return strcmp(oMask->cpName, name);
}

uint64_t Mask_getPos(Mask_T oMask) {
    return oMask->ullMask;
}

void Mask_place(Mask_T oMask, Square_T oSqr) {
    oMask->ullMask |= Square_bitMask(oSqr);
}

void Mask_capture(Mask_T oMask, Square_T oSqr) {
    oMask->ullMask &= ~Square_bitMask(oSqr);
}

bool Mask_isCovered(Mask_T oMask, int r, int f) {
    Square_T sqr = Square_newCoords(r, f);
    bool covered = oMask->ullMask >> Square_bitPos(sqr) & 1;
    Square_free(sqr);
    return covered;
}

char *Mask_toString(Mask_T oMask) {
    char *pcStrRep = malloc(700);
    if (pcStrRep == NULL)
        return "NO SPACE IN MEMORY";
    
    char *ptr = pcStrRep;

    ptr += sprintf(ptr, "Piece Type: \'%.30s\'", oMask->cpName);

    for (int r = 0; r <= 7; r++) {
        ptr += sprintf(ptr, "\n  +---+---+---+---+---+---+---+---+\n%d |", 8-r);
        for (int f = 0; f <= 7; f++) {
            char *bit = Mask_isCovered(oMask, r, f) ? "X": " ";
            ptr += sprintf(ptr, " %s |", bit);
        }
    }
    ptr += sprintf(ptr, "\n  +---+---+---+---+---+---+---+---+\n");
    ptr += sprintf(ptr, "    a   b   c   d   e   f   g   h  \n");

    return pcStrRep;
}

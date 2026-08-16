/*--------------------------------------------------------------------*/
/* mask.c                                                             */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stdio.h>
#include "mask.h"
#include "string.h"
#include "square.h"

struct Mask
{
    /* piece mask */
    uint64_t ullMask;

    /* piece name */
    char *cpName;
};

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
    free(oMask);
}

/*--------------------------------------------------------------------*/

// buffer must be at least 65 bytes (64 bits + null terminator)
char *uint64_to_binary_string(uint64_t value, char *buffer) {
    buffer[64] = '\0';
    for (int i = 63; i >= 0; i--) {
        buffer[i] = (value & 1) ? '1' : '0';
        value >>= 1;
    }
    return buffer;
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

char *Mask_toString(Mask_T oMask) {
    char *name = oMask->cpName;
    char *pcStrRep;
    
    pcStrRep = malloc(200);
    if (pcStrRep == NULL)
        return "NO SPACE IN MEMORY";

    uint64_to_binary_string(oMask->ullMask, pcStrRep);
    sprintf(pcStrRep, "%s\n", oMask->cpName);

    return pcStrRep;
}

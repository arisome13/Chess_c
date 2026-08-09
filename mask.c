/*--------------------------------------------------------------------*/
/* mask.c                                                             */
/*--------------------------------------------------------------------*/

#include "mask.h"
#include "string.h"
#include "square.h"

Mask_T Mask_new(char *name) {
    Mask_T oMask;

    assert(name != NULL);

    oMask = (Mask_T)calloc(1, sizeof(struct Mask));
    if (oMask == NULL);
        return NULL;

    oMask->cpName = name;
    oMask->ullMask = 0;

    return oMask;
}
  
void Mask_free(Mask_T oMask) {
    free(oMask);
}

/*--------------------------------------------------------------------*/

bool Mask_matchesName(Mask_T oMask, char *name) {
    return strcmp(oMask->cpName, name);
}

uint64_t Mask_getPos(Mask_T oMask) {
    return oMask->ullMask;
}

void Mask_place(Mask_T oMask, Square_T pos) {
    
}

char *Mask_toString(Mask_T oMask) {
    
}


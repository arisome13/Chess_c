/*--------------------------------------------------------------------*/
/* castles.c                                                          */
/*--------------------------------------------------------------------*/

#include "castles.h"
#include <assert.h>

struct Castles
{
    /* kingside white */
    bool bKW;
    /* queenside white */
    bool bQW;
    /* kingside black */
    bool bKB;
    /* queenside black */
    bool bQB;
};

Castles_T Castles_new (void) {
    Castles_T oCastles = (Castles_T)calloc(1, sizeof(struct Castles));
    MEM_CHECK(oCastles);

    oCastles->bKW = false;
    oCastles->bQW = false;
    oCastles->bKB = false;
    oCastles->bQB = false;

    return oCastles;
}

void Castles_free (Castles_T oCastles) {
    free(oCastles);
}

void Castles_add (Castles_T oCastles, char castleType) {
    switch (castleType)
    {
        case 'K':
            if (oCastles->bKW)
                break; /* go to after switch */
            oCastles->bKW = true;
            return;
        case 'Q':
            if (oCastles->bQW)
                break; /* go to after switch */
            oCastles->bQW = true;
            return;
        case 'k':
            if (oCastles->bKB)
                break; /* go to after switch */
            oCastles->bKB = true;
            return;
        case 'q':
            if (oCastles->bQB)
                break; /* go to after switch */
            oCastles->bQB = true;
            return;
        default:
            ERROR("Invalid castle type: %c", castleType);
    }
    ERROR("Tried to turn on an already on castle type: %c", castleType);
}

Castles_T Castles_copy (Castles_T oCastles) {
    Castles_T ocCopy = (Castles_T)calloc(1, sizeof(struct Castles));
    MEM_CHECK(oCastles);

    ocCopy->bKW = oCastles->bKW;
    ocCopy->bQW = oCastles->bQW;
    ocCopy->bKB = oCastles->bKB;
    ocCopy->bQB = oCastles->bQB;

    return ocCopy;
}

const char *Castles_toString (Castles_T oCastles) {
    assert(oCastles != NULL);
    if (oCastles->bKW) {
        if (oCastles->bQW) {
            if (oCastles->bKB) {
                if (oCastles->bQB)
                    return "KQkq";
                else
                    return "KQk";
            } else {
                if (oCastles->bQB) {
                    return "KQq";
                } else {
                    return "KQ";
                }
            }
        } else {
            if (oCastles->bKB) {
                if (oCastles->bQB)
                    return "Kkq";
                else
                    return "Kk";
            } else {
                if (oCastles->bQB) {
                    return "Kq";
                } else {
                    return "K";
                }
            }
        }
    } else {
        if (oCastles->bQW) {
            if (oCastles->bKB) {
                if (oCastles->bQB)
                    return "Qkq";
                else
                    return "Qk";
            } else {
                if (oCastles->bQB) {
                    return "Qq";
                } else {
                    return "Q";
                }
            }
        } else {
            if (oCastles->bKB) {
                if (oCastles->bQB)
                    return "kq";
                else
                    return "k";
            } else {
                if (oCastles->bQB) {
                    return "q";
                } else {
                    return "-";
                }
            }
        }
    }
}

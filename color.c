
#include "color.h"

const char *Color_toString(enum color c) {
    switch (c) {
        case BLACK:
            return "BLACK";
        case WHITE:
            return "WHITE";
        default:
            return "UNKNOWN";
    }
}

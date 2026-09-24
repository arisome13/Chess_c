
#include "color.h"

p_color Color_oposite(p_color c) {
    switch (c) {
        case BLACK:
            return WHITE;
        case WHITE:
            return BLACK;
        default:
            return NO_COLOR;
    }
}

const char *Color_toString(p_color c) {
    switch (c) {
        case BLACK:
            return "BLACK";
        case WHITE:
            return "WHITE";
        default:
            return "UNKNOWN";
    }
}

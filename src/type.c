
#include "type.h"
#include <stdio.h>
#include <stdlib.h>

int Type_getValue (p_type type, p_color color) {
    int value = 0;
    int mod = -1;

    if (color == WHITE)
        mod = 1;

    switch (type)
    {
        case PAWN:
            value = 1;
            break;
        case KNIGHT:
        case BISHOP:
            value = 3;
            break;
        case ROOK:
            value = 5;
            break;
        case QUEEN:
            value = 9;
            break;
        case KING:
            return 0;
        default:
            printf("Invalid type: #%d", type);
            exit(1);
    }

    return value * mod;
}

char Type_toString(p_type type, p_color color) {

    char tcStr;

    switch (type)
    {
        case PAWN:
            tcStr = 'p';
            break;
        case KNIGHT:
            tcStr = 'n';
            break;
        case BISHOP:
            tcStr = 'b';
            break;
        case ROOK:
            tcStr = 'r';
            break;
        case QUEEN:
            tcStr = 'q';
            break;
        case KING:
            tcStr = 'k';
            break;
        default:
            printf("Invalid type: %d", type);
            exit(1);
    }

    if (color == WHITE)
        tcStr -= 32;

    return tcStr;
}

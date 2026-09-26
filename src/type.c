
#include "type.h"
#include "printers.h"
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
            ERROR("Invalid type: #%d", type);
    }

    return value * mod;
}

char Type_toString(p_type type, p_color color) {

    char tcStr = '\0';

    if (type == NO_TYPE || color == NO_COLOR)
        return '#';

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
            ERROR("Invalid type: %d\n", type);
    }

    if (color == WHITE)
        tcStr -= 32;

    return tcStr;
}

const char *Type_nameToSymbol (char name) {
    //'a', 'A', 'Z', 'z';
    int isWhite = name < 90;
    
    if (isWhite)
        name += 32;

    if (name == 'p')
        return isWhite ? "♙" : "♟";
    else if (name == 'r')
        return isWhite ? "♖" : "♜";
    else if (name == 'n')
        return isWhite ? "♘" : "♞";
    else if (name == 'b')
        return isWhite ? "♗" : "♝";
    else if (name == 'q')
        return isWhite ? "♕" : "♛";
    else if (name == 'k')
        return isWhite ? "♔" : "♚";
    else {
        ERROR("Invalid piece name %c\n", name);
        return "";
    }
}

/*
    ♜	♞	♝	♛	♚	♝	♞	♜
    ♟	♟	♟	♟	♟	♟	♟	♟
    ♙	♙	♙	♙	♙	♙	♙	♙
    ♖	♘	♗	♕	♔	♗	♘	♖
*/


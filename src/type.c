#include <type.h>
#include <stdio.h>
#include <stdlib.h>

int Type_getValue (char name) {
    int value = 0;
    int mod = -1;

    /* switch upper case to lower case */
    if ('A' <= name && name <= 'Z') {
        name += 32;
        mod = 1;
    }

    switch (name)
    {
        case 'p':
            value = 1;
            break;
        case 'n':
        case 'b':
            value = 3;
            break;
        case 'r':
            value = 5;
            break;
        case 'q':
            value = 9;
            break;
        case 'k':
            return 0;
        default:
            printf("Invalid type: %c", name);
            exit(1);
    }

    return value * mod;
}
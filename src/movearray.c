/*--------------------------------------------------------------------*/
/* movearray.c                                                        */
/*--------------------------------------------------------------------*/

#include "movearray.h"

struct MoveArray
{
    /* pointer to an array of moves */
    Move_T paMoves[MAX_MOVES_IN_ARRAY];

    /* length of the array (number of moves in the array) */
    size_t ulArrLen;
};


/*--------------------------------------------------------------------*/

MoveArray_T MoveArray_new (void) {
    MoveArray_T omArray = (MoveArray_T)calloc(1, sizeof(struct MoveArray));
    CHECK_MEM(omArray);

    omArray->ulArrLen = 0;

    return omArray;
}
void MoveArray_free (MoveArray_T omArray) {
    CHECK_NULL(omArray);
    
    for (size_t i = 0; i < omArray->ulArrLen; i++)
        Move_free(omArray->paMoves[i]);

    free(omArray);
}
// MoveArray_T MoveArray_copy (MoveArray_T omArray);

/*--------------------------------------------------------------------*/

void MoveArray_add (MoveArray_T omArray, Move_T oMove) {
    CHECK_NULL(omArray);
    CHECK_NULL(oMove);

    if (omArray->ulArrLen >= MAX_MOVES_IN_ARRAY)
        ERROR("Cannot add more moves to this MoveArray, it is full.\n");

    omArray->paMoves[omArray->ulArrLen] = Move_copy(oMove);
    omArray->ulArrLen++;
}
Move_T MoveArray_get (MoveArray_T omArray, size_t index) {
    CHECK_NULL(omArray);
    if (index >= MAX_MOVES_IN_ARRAY)
        ERROR("Index out of bounds: %zu > %zu.\n", index, MAX_MOVES_IN_ARRAY);
    if (index >= omArray->ulArrLen)
        return NULL;
    return omArray->paMoves[index];
}

/*--------------------------------------------------------------------*/

char *MoveArray_toString (MoveArray_T omArray) {
    CHECK_NULL(omArray);

    int MAX_MOVE_LEN = 4;

    char *pcStr = malloc(sizeof(char) * MAX_MOVE_LEN * MAX_MOVES_IN_ARRAY);
    PRINT("Number of bites for move array string: %d\n", sizeof(char) * 5 * MAX_MOVES_IN_ARRAY);
    char *ptr = pcStr;

    ptr += snprintf(ptr, 14, "Move Array: [");

    for (size_t i = 0; i < MAX_MOVES_IN_ARRAY; i++) {
        if (i > 0)
            ptr += snprintf(ptr, 3, ", ");

        Move_T move = MoveArray_get(omArray, i);
        if (move == NULL)
            break;
        
        char *movestr = Move_toString(move);
        ptr += snprintf(ptr, MAX_MOVE_LEN, "%s", movestr);
        free(movestr);
    }

    ptr += snprintf(ptr, 2, "]");
    return pcStr;
}


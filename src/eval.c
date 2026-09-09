/*--------------------------------------------------------------------*/
/* eval.c                                                           */
/*--------------------------------------------------------------------*/

#include "eval.h"

struct Eval
{
    /* type of eval: centipawn or forced mate */
    eval_type type;
    
    /* eval score */
    int score;
};

Eval_T Eval_new(enum eval_type type, int score) {
    Eval_T oEval;

    oEval = (Eval_T)calloc(1, sizeof(struct Eval));
    CHECK_MEM(oEval);

    oEval->type = type;
    oEval->score = score;

    return oEval;
}

void Eval_free(Eval_T oEval) {
    CHECK_NULL(oEval);
    free(oEval);
}

/*--------------------------------------------------------------------*/

char *Eval_toString(Eval_T oEval) {
    char *pcStrRep = (char *)malloc(20);
    CHECK_MEM(pcStrRep);

    char *ptr = pcStrRep;

    if (oEval->type == CENTIPAWN)
        ptr += sprintf(ptr, "CP");
    else
        ptr += sprintf(ptr, "FM");
    ptr += sprintf(ptr, ": %d\n", oEval->score);

    return pcStrRep;
}

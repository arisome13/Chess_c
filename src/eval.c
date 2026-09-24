/*--------------------------------------------------------------------*/
/* eval.c                                                           */
/*--------------------------------------------------------------------*/

#include "eval.h"

struct Eval
{
    /* type of eval: centipawn or forced mate */
    eval_type type;
    
    /* eval score */
    double score;
};

Eval_T Eval_new(enum eval_type type, double score) {
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

enum {MATE = 10000};
static long Eval_key (Eval_T eval) {
    CHECK_NULL(eval);

    if (eval->type == CENTIPAWN)
        return eval->score;

    assert(eval->type == FORCED_MATE && eval->score != 0);
    if (eval->score > 0)
        return MATE - eval->score;
    else
        return -MATE - eval->score;
}
int Eval_compare (Eval_T oEval1, Eval_T oEval2) {
    CHECK_NULL(oEval1);
    CHECK_NULL(oEval2);

    long k1 = Eval_key(oEval1);
    long k2 = Eval_key(oEval2);

    if (k1 > k2) 
        return 1;
    else if (k1 < k2) 
        return -1;
    else 
        return 0;
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
    ptr += sprintf(ptr, ": %f\n", oEval->score);

    return pcStrRep;
}

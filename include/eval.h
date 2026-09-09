/*--------------------------------------------------------------------*/
/* eval.h.                                                            */
/*--------------------------------------------------------------------*/

#include "helpers.h"

#ifndef EVAL_INCLUDED
#define EVAL_INCLUDED

/* An Eval_T object holds an evaluation of a chess position. + if 
    the position is favorable for white, - if it is favorable for 
    black. CALLER FREE. */
typedef struct Eval *Eval_T;

/* the type of evals there can be: 
    cp: compares the number of "centipawn points"
    mate: moves till forced mate (mate in #) */
typedef enum eval_type {CENTIPAWN, FORCED_MATE} eval_type;

/* Return a new Eval_T object initialized to type and score. 
    CALLER FREE. */
Eval_T Eval_new (eval_type type, int score);

/* Free oEval. */
void Eval_free (Eval_T oEval);

/* Return a string representation of oEval. CALLER FREE. */
char *Eval_toString (Eval_T oEval);

#endif
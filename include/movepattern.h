/*--------------------------------------------------------------------*/
/* movepattern.h                                                      */
/*--------------------------------------------------------------------*/

#include "helpers.h"
#include <mask.h>
#include <move.h>

#ifndef MOVEPATTERN_H
#define MOVEPATTERN_H

/* defines the three type of moves you can have: 1) a move that has to 
    capture, 2) a move that can't capture, 3) and a move that can do 
    either. */
typedef enum CaptureRule {ONLY_CAPTURE, CANT_CAPTURE, BOTH} CaptureRule;

/* A Movement is a direction a piece can move in and if it can repeat 
    that move. */
struct Movement
{
    // direction of movement
    int dx, dy;
    // number of times movement can be repeated (0 == infinity)
    size_t num_reps;
    // rule for if this movement has to or can't capture
    CaptureRule end;
};

/* A MovePattern_T object holds the different types of moves a piece 
    can make. */
typedef struct MovePattern *MovePattern_T;

enum {MAX_MOVE_TYPES = 8};

/*--------------------------------------------------------------------*/

/* Return a new MovePattern_T object initialized to empty. 
    CALLER FREE. */
MovePattern_T MovePattern_new (void);

/* Free oPattern. */
void MovePattern_free (MovePattern_T oPattern);

/* Return a deep copy of oPattern. CALLER FREE. */
MovePattern_T MovePattern_copy (MovePattern_T oPattern);

/*--------------------------------------------------------------------*/

/* Adds a move in direction (dx, dy) to oPattern. */
void MovePattern_add (MovePattern_T oPattern, 
    int dy, int dx, size_t reps, CaptureRule end);

/* Returns a mask of the squares oMove goes through, or NULL if the 
    move cannot be made with oPattern. CALLER FREE. */
Mask_T MovePattern_canMove (MovePattern_T oPattern, Move_T oMove, bool isCapture);

/* Returns the move pattern for type and color. CALLER FREE. */
MovePattern_T MovePattern_for (p_type type, p_color color);

/* Returns the ith Movement held by oPattern. */
struct Movement *MovePattern_getMovement(MovePattern_T oPattern, int i);

/*--------------------------------------------------------------------*/

/* Return a string representation of oPattern. CALLER FREE. */
char *MovePattern_toString (MovePattern_T oPattern);
char *MovePattern_showMovesFrom (MovePattern_T oPattern, Square_T oSqr);

#endif

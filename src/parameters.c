/*--------------------------------------------------------------------*/
/* parameters.c                                                       */
/*--------------------------------------------------------------------*/

#include <stdio.h> 
#include <string.h>
#include "parameters.h"

struct ChessParameters
{
   /* color of the current play*/
   enum color cTurnColor;

   /* available castle indicators */
   char *pcCastles;

   /* enpassant square */
   Square_T sqrEnpassant;

   /* half move count for 50 move rule */
   int i50MoveCount;

   /* current full move */
   int iCurrMove;
};

ChessParameters_T ChessParameters_new(const char *pcFen) {
   ChessParameters_T oParams;
   int fenIndex;
   char pcEnpTemp[3];
   char *pcEndStr;

   
   oParams = (ChessParameters_T)calloc(1, 
            sizeof(struct ChessParameters));
   if (oParams == NULL)
      return NULL;

   /* get fenIndex to the first element in a fen string: 
      the turn color */
   fenIndex = 0;
   while (pcFen[fenIndex++] != ' ') {}
   
   if (pcFen[fenIndex] == 'w')
      oParams->cTurnColor = WHITE;
   else if (pcFen[fenIndex] == 'b')
      oParams->cTurnColor = BLACK;
   else {
      ERROR("Impropper turn color char: %c", pcFen[fenIndex]);
   }
   fenIndex += 2; /* move index to castling section */

   oParams->pcCastles = malloc(10);
   oParams->pcCastles[0] = '\0';
   while (pcFen[fenIndex] != ' ') {
      strncat(oParams->pcCastles, &pcFen[fenIndex], 1);
      fenIndex++;
   }
   fenIndex++; /* move index to enpassant section */

   oParams->sqrEnpassant = NULL;
   if (pcFen[fenIndex] != '-') {
      strncpy(pcEnpTemp, &pcFen[fenIndex], 2);
      oParams->sqrEnpassant = Square_newNotation(pcEnpTemp);
      fenIndex++;
   }
   fenIndex += 2; /* move index to 50 move rule section */

   oParams->i50MoveCount = strtol(pcFen + fenIndex, &pcEndStr, 10);
   oParams->iCurrMove = strtol(pcEndStr, &pcEndStr, 10);

   return oParams;
}

void ChessParameters_free(ChessParameters_T oParams) {
   free(oParams->sqrEnpassant);
   free(oParams);
}

enum color ChessParameters_turnColor(ChessParameters_T oParams) {
   return oParams->cTurnColor;
}
char *ChessParameters_castles(ChessParameters_T oParams) {
   return oParams->pcCastles;
}
Square_T ChessParameters_enpSqr(ChessParameters_T oParams) {
   return oParams->sqrEnpassant;
}
int ChessParameters_50MoveRule(ChessParameters_T oParams) {
   return oParams->i50MoveCount;
}
int ChessParameters_numMoves(ChessParameters_T oParams) {
   return oParams->iCurrMove;
}

char *ChessParameters_toString(ChessParameters_T oParams) {
   char *pcStrRep;
   char *pcSqr = oParams->sqrEnpassant == NULL ? "--" : Square_getNotation(oParams->sqrEnpassant);

   asprintf(&pcStrRep, 
      "  +-------+------+----+---+---+\n  | %s | %s | %s | %d | %d |\n  +-------+------+----+---+---+\n", 
      Color_toString(oParams->cTurnColor), 
      oParams->pcCastles, 
      pcSqr,
      oParams->i50MoveCount, 
      oParams->iCurrMove);

   if (oParams->sqrEnpassant != NULL)
      free(pcSqr);

   return pcStrRep;
}

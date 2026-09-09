/*--------------------------------------------------------------------*/
/* parameters.c                                                       */
/*--------------------------------------------------------------------*/

#include "parameters.h"

struct ChessParameters
{
   /* color of the current play */
   p_color cTurnColor;

   /* available castle indicators */
   Castles_T oCastles;

   /* enpassant square or NULL */
   Square_T oEnpSqr;

   /* half move count for 50 move rule */
   size_t i50MoveCount;

   /* current full move */
   size_t iCurrMove;
};

ChessParameters_T ChessParameters_new(const char *pcFen) {
   size_t fenIndex;
   char pcEnpTemp[3];
   char *pcEndStr;

   ChessParameters_T oParams = (ChessParameters_T)calloc(1, 
            sizeof(struct ChessParameters));
   CHECK_MEM(oParams);
   
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

   oParams->oCastles = Castles_new();
   while (pcFen[fenIndex] != ' ') {
      Castles_add(oParams->oCastles, pcFen[fenIndex]);
      fenIndex++;
   }
   fenIndex++; /* move index to enpassant section */

   oParams->oEnpSqr = NULL;
   if (pcFen[fenIndex] != '-') {
      strncpy(pcEnpTemp, &pcFen[fenIndex], 2);
      oParams->oEnpSqr = Square_newNotation(pcEnpTemp);
      fenIndex++;
   }
   fenIndex += 2; /* move index to 50 move rule section */

   oParams->i50MoveCount = strtol(pcFen + fenIndex, &pcEndStr, 10);
   oParams->iCurrMove = strtol(pcEndStr, &pcEndStr, 10);

   return oParams;
}

void ChessParameters_free(ChessParameters_T oParams) {
   free(oParams->oEnpSqr);
   free(oParams->oCastles);
   free(oParams);
}

ChessParameters_T ChessParameters_copy(ChessParameters_T oParams) {
   ChessParameters_T opCopy = (ChessParameters_T)calloc(1, 
            sizeof(struct ChessParameters));
   CHECK_MEM(oParams);

   opCopy->cTurnColor = oParams->cTurnColor;
   opCopy->oCastles = Castles_copy(oParams->oCastles);
   if (oParams->oEnpSqr != NULL)
      opCopy->oEnpSqr = Square_copy(oParams->oEnpSqr);
   else
      opCopy->oEnpSqr = NULL;
   opCopy->i50MoveCount = oParams->i50MoveCount;
   opCopy->iCurrMove = oParams->iCurrMove;

   return opCopy;
}

/*--------------------------------------------------------------------*/

p_color ChessParameters_turnColor(ChessParameters_T oParams) {
   return oParams->cTurnColor;
}

Castles_T ChessParameters_castles(ChessParameters_T oParams) {
   return oParams->oCastles;
}

Square_T ChessParameters_enpSqr(ChessParameters_T oParams) {
   return oParams->oEnpSqr;
}

size_t ChessParameters_50MoveRule(ChessParameters_T oParams) {
   return oParams->i50MoveCount;
}

size_t ChessParameters_numMoves(ChessParameters_T oParams) {
   return oParams->iCurrMove;
}

/*--------------------------------------------------------------------*/

void ChessParameters_incrementMove (
   ChessParameters_T oParams, bool wasPawnOrCapture) {
      CHECK_NULL(oParams);

      /* increment move count */
      oParams->iCurrMove++;
      if (!wasPawnOrCapture)
         oParams->i50MoveCount++;
      
      /* change turn color */
      if (oParams->cTurnColor == BLACK)
         oParams->cTurnColor = WHITE;
      else
         oParams->cTurnColor = BLACK;
      
      oParams->oEnpSqr = NULL;
}

void ChessParameters_setEnpSqr (
   ChessParameters_T oParams, Square_T oSqr) {
      CHECK_NULL(oParams);
      CHECK_NULL(oSqr);
      Square_free(oParams->oEnpSqr);
      oParams->oEnpSqr = oSqr;
}

void ChessParameters_removeCastle (
   ChessParameters_T oParams, char castle) {
      CHECK_NULL(oParams);
      Castles_remove(oParams->oCastles, castle);
}

/*--------------------------------------------------------------------*/

char *ChessParameters_toString(ChessParameters_T oParams) {
   char *pcStrRep;
   char *pcSqr = oParams->oEnpSqr == NULL ? "--" : Square_toString(oParams->oEnpSqr);

   asprintf(&pcStrRep, 
      "  +-------+------+----+---+---+\n  | %s | %s | %s | %zu | %zu |\n  +-------+------+----+---+---+", 
      Color_toString(oParams->cTurnColor), 
      Castles_toString(oParams->oCastles), 
      pcSqr,
      oParams->i50MoveCount, 
      oParams->iCurrMove);

   if (oParams->oEnpSqr != NULL)
      free(pcSqr);

   return pcStrRep;
}

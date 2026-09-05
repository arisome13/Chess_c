/*--------------------------------------------------------------------*/
/* error.h                                                           */
/*--------------------------------------------------------------------*/

#ifndef ERROR_INCLUDED
#define ERROR_INCLUDED

#include <string.h>
#include <stdio.h>

void ERROR(const char *pcMessage, ...);
void MEM_CHECK(void *pObject);
void PRINT(const char *pcMessage, ...);

#endif
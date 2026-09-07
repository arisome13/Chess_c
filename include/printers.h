/*--------------------------------------------------------------------*/
/* error.h                                                           */
/*--------------------------------------------------------------------*/

#ifndef ERROR_INCLUDED
#define ERROR_INCLUDED

#include <string.h>
#include <stdio.h>

/* use for: catching memory errors after initialization */
void CHECK_MEM(void *pObject);

/* use for: catching null parameters */
void CHECK_NULL(void *pObject);

/* use for: catching out of bounds errors */
void CHECK_COORDS(size_t x, size_t y);

/* use for: catching unexpected errors */
void ERROR(const char *pcMessage, ...);

/* use for printing some message */
void PRINT(const char *pcMessage, ...);

#endif
/*--------------------------------------------------------------------*/
/* error.h                                                           */
/*--------------------------------------------------------------------*/

#ifndef ERROR_INCLUDED
#define ERROR_INCLUDED

#include <string.h>
#include <stdio.h>

/* use for: catching memory errors after initialization */
void CHECK_MEM(const void *pObject);

/* use for: catching null parameters */
void CHECK_NULL(const void *pObject);

/* use for: catching out of bounds errors */
void CHECK_COORDS(size_t y, size_t x, const char *location);

/* use for: catching unexpected errors */
void ERROR(const char *pcMessage, ...);

/* use for printing some message */
void PRINT(const char *pcMessage, ...);

#endif
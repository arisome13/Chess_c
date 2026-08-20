/*--------------------------------------------------------------------*/
/* error.h                                                           */
/*--------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void ERROR(const char *pcMessage, ...)
{
    va_list args;
    va_start(args, pcMessage);

    vprintf(pcMessage, args);
    
    va_end(args);
    exit(EXIT_FAILURE);
}

void MEM_CHECK(void *pObject) {
    if (pObject == NULL)
        ERROR("Memory error.");
}

/*--------------------------------------------------------------------*/
/* error.h                                                           */
/*--------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdarg.h>
#include "printers.h"

void ERROR(const char *pcMessage, ...)
{
    va_list args;
    va_start(args, pcMessage);

    printf("\n------ ERROR ------\n");
    vprintf(pcMessage, args);
    
    va_end(args);
    exit(EXIT_FAILURE);
}

void CHECK_MEM(const void *pObject) {
    if (pObject == NULL)
        ERROR("Memory error.\n");
}

void CHECK_COORDS(size_t y, size_t x, const char *location) {
    if (!(0 <= x && x < 8 && 0 <= y && y < 8))
        ERROR("Invalid coordinates from %s(). %zu, %zu must be in [0, 7]", location, y, x);
}

void PRINT(const char *pcMessage, ...)
{
    va_list args;
    va_start(args, pcMessage);

    vprintf(pcMessage, args);
    
    va_end(args);
}

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

void CHECK_NULL(void *pObject) {
    if (pObject == NULL)
        ERROR("Null error.\n");
}
void CHECK_MEM(void *pObject) {
    if (pObject == NULL)
        ERROR("Memory error.\n");
}

void CHECK_COORDS(size_t x, size_t y) {
    if (!(0 <= x && x < 8 && 0 <= y && y < 8))
        ERROR("Invalid coordinates. x, y must be in [0, 7]");
}

void PRINT(const char *pcMessage, ...)
{
    va_list args;
    va_start(args, pcMessage);

    vprintf(pcMessage, args);
    
    va_end(args);
    exit(EXIT_FAILURE);
}

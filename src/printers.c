/*--------------------------------------------------------------------*/
/* printers.c                                                         */
/*--------------------------------------------------------------------*/


#include "printers.h"

void print_message(const char *pcMessage, ...) {
    va_list args;
    va_start(args, pcMessage);
    vprintf(pcMessage, args);
    va_end(args);
}

void error_message(const char *function_name, 
        const char *pcMessage, ...) {
    va_list args;
    va_start(args, pcMessage);
    printf("\n----- ERROR @ %s -----\n", function_name);
    vprintf(pcMessage, args);
    va_end(args);
    exit(EXIT_FAILURE);
}
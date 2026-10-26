/*--------------------------------------------------------------------*/
/* printers.c                                                         */
/*--------------------------------------------------------------------*/


#include "printers.h"

void error_message(const char *file_name, const char *function_name, 
        int line_num, const char *pcMessage, ...) {
    va_list args;
    va_start(args, pcMessage);
    printf("\n----- ERROR - %s:%d in %s() -----\n", file_name, line_num, function_name);
    vprintf(pcMessage, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

void print_message(const char *pcMessage, ...) {
    va_list args;
    va_start(args, pcMessage);
    vprintf(pcMessage, args);
    va_end(args);
}

/*--------------------------------------------------------------------*/
/* printers.h                                                         */
/*--------------------------------------------------------------------*/

#include <stdarg.h>
#include <stdlib.h>

#ifndef PRINTERS_H
#define PRINTERS_H

#include <string.h>
#include <stdio.h>

// 1 == true, 0 == false
#define DEBUG   1

void print_message(const char *pcMessage, ...);
void error_message(const char *function_name, 
        const char *pcMessage, ...);

#if DEBUG // debugging macro functions

    /* use for: catching unexpected errors */
    #define ERROR(pcMessage, ...) \
        do { \
            error_message(__func__, pcMessage __VA_OPT__(,) __VA_ARGS__); \
        } while (0)

    /* use for printing some message */
    #define PRINT(pcMessage, ...) \
        do { \
            print_message(pcMessage __VA_OPT__(,) __VA_ARGS__); \
        } while (0)

    /* use for: catching memory errors after initialization */
    #define CHECK_MEM(pObject) \
        do { \
            if ((pObject) == NULL) \
                ERROR("Memory error at %s.\n", __func__); \
        } while (0)

    /* use for: catching null parameters */
    #define CHECK_NULL(pObject) \
        do { \
            if (pObject == NULL) \
                ERROR("Null error @ %s\n", __func__); \
        } while(0)

    /* use for: catching out of bounds errors */
    #define CHECK_COORDS(y, x) \
        do { \
            if (!(0 <= x && x < 8 && 0 <= y && y < 8)) \
                ERROR("Invalid coordinates. %zu, %zu must be in [0, 7]\n", y, x); \
        } while(0)

#else // NO_DEBUG

    #define CHECK_MEM(pObject) ((void)0)
    #define CHECK_NULL(pObject) ((void)0)
    #define CHECK_COORDS(y, x) ((void)0)

#endif // DEBUG

#endif // PRINTERS_H
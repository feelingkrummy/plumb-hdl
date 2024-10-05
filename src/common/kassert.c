#include <stdio.h>
#include <stdarg.h>

#include "kassert.h"

void print_error(
        // AssertLevel level,
        const char* message,
        const char* file_name,
        int line_num,
        const char* func,
        const char* expr,
        ...
) {
    fprintf(stderr, "%s in %s @ %d : Assertion ( %s ) failed. ", func, file_name, line_num, expr);

    va_list args;
    va_start(args, expr);
    vfprintf(stderr, message, args);
    va_end(args);

    fprintf(stderr, "\n");
}

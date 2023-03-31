#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug/debug.h"
#include "error_handling.h"

void handle_error(const char* msg)
{
    debug();

    perror(msg);
    exit(EXIT_FAILURE);
}

void handle_error_en(const char* msg, int en)
{
    debug();

    errno = en;
    handle_error(msg);
}

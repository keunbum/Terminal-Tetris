#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "error_handling.h"

void handle_error(const char* msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void handle_error_num(const char* msg, int error_num)
{
    errno = error_num;
    handle_error(msg);
}

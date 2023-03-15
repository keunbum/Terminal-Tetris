#include <stdio.h>
#include <stdlib.h>

#include "error_handling.h"

void handle_error(const char* message)
{
    perror(message);
    exit(EXIT_FAILURE);
}
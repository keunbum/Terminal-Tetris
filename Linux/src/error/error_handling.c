#include "error_handling.h"

void error_handling(const char* message)
{
    perror(message);
    exit(1);
}

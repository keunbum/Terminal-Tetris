#include <stdlib.h>
#include <time.h>

#include "random.h"

void init_rng(unsigned int seed)
{
    srand(seed);
}

unsigned int rng(void)
{
    return (unsigned int)rand();
}
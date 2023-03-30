#include <stdlib.h>
#include <time.h>

#include "debug/debug.h"
#include "random.h"

void init_rng(unsigned int seed)
{
    debug();

    srand(seed);
}

unsigned int rng(void)
{
    debug();
    
    return (unsigned int)rand();
}
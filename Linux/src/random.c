#include <stdlib.h>
#include <time.h>

#include "debug.h"
#include "random.h"

/* Can't this be objectified?? */

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
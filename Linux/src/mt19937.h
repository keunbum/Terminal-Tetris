#ifndef __MT19937__H
#define __MT19937__H

#include <stdint.h>

#include "util.h"

void mt19937_srand(uint32_t seed);
uint32_t mt19937_rng(void);

static inline uint32_t rng(void)
{
    return mt19937_rng();
}

/* [st, en) */
static inline int32_t rng_range(int32_t st, int32_t en)
{
    uint32_t n = en - st;
    return (int32_t) (rng() % n) + st;
}

#endif /* __MT19937__H */
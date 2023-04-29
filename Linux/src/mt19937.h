#ifndef __MT19937__H
#define __MT19937__H

#include <stdint.h>

#include "util.h"

void mt19937_srand(uint32_t seed);
uint32_t mt19937_rng(void);

static inline void init_mt19937(uint32_t seed)
{
    mt19937_srand(seed);
}

static inline uint32_t rng(void)
{
    return mt19937_rng();
}

// [s, e)
static inline int32_t rng_range(int32_t s, int32_t e)
{
    uint32_t n = e - s;
    return (int32_t) (rng() % n) + s;
}

// [first, last)
static inline void shuffle_int(int* first, int* last)
{
    for (int i = (int) (last - first) - 1; i > 0; --i) {
        swap_int(first + i, first + rng_range(0, i + 1));
    }
}

#endif /* __MT19937__H */
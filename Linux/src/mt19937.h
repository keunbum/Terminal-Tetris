#ifndef __MT19937__H
#define __MT19937__H

#include <stdint.h>

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

#endif /* __MT19937__H */
#ifndef __MT19937__H
#define __MT19937__H

#include <stdint.h>

void mt19937_srand(uint32_t seed);
uint32_t mt19937_rng(void);

#define init_rng(seed) mt19937_srand(seed)
#define rng() mt19937_rng()

#endif /* __MT19937__H */
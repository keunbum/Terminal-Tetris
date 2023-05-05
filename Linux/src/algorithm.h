#ifndef __ALGORITHM__H
#define __ALGORITHM__H

#include "mt19937.h"

static inline long max_long(long a, long b)
{
    return a > b ? a : b;
}

static inline void swap_int(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static inline void iota_int(int* first, int* last, int val)
{
    while (first != last) {
        *first++ = val++;
    }
}

// [first, last)
static inline void shuffle_int(int* first, int* last)
{
    for (int i = (int) (last - first) - 1; i > 0; --i) {
        swap_int(first + i, first + rng_range(0, i + 1));
    }
}

#endif /* __ALGORITHM__H */
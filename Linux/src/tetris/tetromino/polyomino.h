#ifndef __POLYOMINO__H
#define __POLYOMINO__H

#include "stdbool.h"

typedef int polyomino_matrix_t;
typedef int polyomino_matrix_n_t;

static inline bool is_empty_block(polyomino_matrix_t m, int pos)
{
    return ((m >> pos) & 1) == 0;
}

#endif /* __POLYOMINO__H */
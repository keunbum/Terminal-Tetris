#ifndef __POS__H
#define __POS__H

#include <stdbool.h>

#define DECLARE_POS_T(T) \
    typedef struct {     \
        T x;             \
        T y;             \
    } pos_t

// DECLARE_POS_T(double);

typedef int pos_e_t;

DECLARE_POS_T(pos_e_t);

static inline bool is_equal_pos(const pos_t* pos_a, const pos_t* pos_b)
{
    return pos_a->x == pos_b->x && pos_a->y == pos_b->y;
}

#endif /* __POS__H */
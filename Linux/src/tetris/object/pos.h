#ifndef __POS__H
#define __POS__H

#include <stdbool.h>

#define DECLARE_POS_T(T) \
    typedef struct {     \
        T x;             \
        T y;             \
    } pos_t

typedef float pos_e_t;

DECLARE_POS_T(pos_e_t);

static inline void set_pos(pos_t* const out_pos, pos_e_t pos_x, pos_e_t pos_y)
{
    out_pos->x = pos_x;
    out_pos->y = pos_y;
}

#endif /* __POS__H */
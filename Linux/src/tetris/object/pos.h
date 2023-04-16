#ifndef __POS__H
#define __POS__H

#include <stdbool.h>

typedef float pos_e_t;

typedef struct {
    pos_e_t x;
    pos_e_t y;
} pos_t;

static inline void set_pos(pos_t* const out_pos, pos_e_t pos_x, pos_e_t pos_y)
{
    out_pos->x = pos_x;
    out_pos->y = pos_y;
}

#endif /* __POS__H */
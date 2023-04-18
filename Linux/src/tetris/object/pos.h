#ifndef __POS__H
#define __POS__H

#include <stdbool.h>

typedef float pos_e_t;

typedef struct {
    pos_e_t x;
    pos_e_t y;
} pos_t;

typedef struct {
    int x;
    int y;
} pos_int_t;

static inline pos_t create_pos(pos_e_t x, pos_e_t y)
{
    pos_t ret = {x, y};
    return ret;
}

static inline pos_t create_pos_empty()
{
    return create_pos(0, 0);
}

static inline pos_int_t create_pos_int(int x, int y)
{
    pos_int_t ret = {x, y};
    return ret;
}

static inline pos_int_t create_pos_int_empty()
{
    return create_pos_int(0, 0);
}

#endif /* __POS__H */
#ifndef __BLOCK__H
#define __BLOCK__H

#include "block_wprint.h"

typedef enum {
    BLOCK_NATURE_EMPTY,
    BLOCK_NATURE_FULL,
} block_nature_t;

typedef struct {
    block_nature_t nature;
    block_wprint_t wprint;
} block_t;

static inline void set_block_each(block_t* const out_block, block_nature_t nature, block_wprint_t wprint)
{
    out_block->nature = nature;
    out_block->wprint = wprint;
}

static inline block_t create_block(block_nature_t nature, block_wprint_t wprint)
{
    block_t ret = { nature, wprint };
    return ret;
}

#endif /* __BLOCK__H */
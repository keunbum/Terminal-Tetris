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

static inline void init_block(block_t* const out_block, block_nature_t nature, block_wprint_t wprint)
{
    out_block->nature;
    out_block->wprint;
}

static inline void get_block_nature(const block_t* block)
{
    return block->nature;
}

static inline void get_block_wprint(const block_t* block)
{
    return block->wprint;
}

#endif /* __BLOCK__H */
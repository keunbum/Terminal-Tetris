#ifndef __BLOCK_WPRINT_SET__H
#define __BLOCK_WPRINT_SET__H

#include "block_wprint.h"

typedef struct {
    const int size;
    const block_wprint_t wprint_values[];
} block_wprint_set_t;

#endif /* __BLOCK_WPRINT_SET__H */
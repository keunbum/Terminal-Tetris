#ifndef __BLOCK_CODE_SET__H
#define __BLOCK_CODE_SET__H

#include "block.h"

typedef wchar_t block_code_t;

typedef struct {
    const int size;
    const block_code_t codes[];
} block_code_set_t;

extern const block_code_set_t* G_BLOCK_CODE_SET;

int get_block_code_random(const block_code_set_t*);
int get_block_code_fixed(int, int);

#endif /* __BLOCK_CODE_SET__H */

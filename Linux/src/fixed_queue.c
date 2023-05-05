#include <stdlib.h>
#include <assert.h>

#include "fixed_queue.h"

void traverse_queue(const fixed_queue_t* que, void (*func)(void* const, int, void*), void* arg)
{
    size_t ptr = que->beg;
    for (int i = 0; i < (int)que->cnt; ++i) {
        func(que->pa[ptr], i, arg);
        ptr = (ptr + 1) & (que->max_size - 1);
    }
}

void init_queue_malloc(fixed_queue_t* const out_que, int max_size)
{
    /* max_size must be a power of 2. */
    out_que->max_size = max_size;
    out_que->beg = 0;
    out_que->end = 0;
    out_que->cnt = 0;
    out_que->pa = (void**)malloc(sizeof(void*) * out_que->max_size);
}

void cleanup_queue_free(fixed_queue_t* const out_que)
{
    free(out_que->pa);
    out_que->pa = NULL;
}
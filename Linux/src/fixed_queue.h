#ifndef __FIXED_QUEUE__H
#define __FIXED_QUEUE__H

#include <stdbool.h>
#include <stddef.h>

#include "debug.h"

/* Implements an array-based circular queue. */
typedef struct {
    size_t max_size;
    size_t beg;
    size_t end;
    size_t cnt;
    void** pa;
} fixed_queue_t;

static inline bool is_queue_empty(const fixed_queue_t* que)
{
    return que->cnt == 0;
}

static inline bool is_queue_full(const fixed_queue_t* que)
{
    return que->cnt == que->max_size;
}

static inline const void* get_queue_top(const fixed_queue_t* que)
{
    return que->pa[que->beg];
}

static inline void push_queue(fixed_queue_t* const out_que, void* tetro)
{
    out_que->pa[out_que->end] = tetro;
    out_que->end = (out_que->end + 1) & (out_que->max_size - 1);
    out_que->cnt += 1;
}

static inline void* pop_queue(fixed_queue_t* const out_que)
{
    void* ret = out_que->pa[out_que->beg];
    out_que->beg = (out_que->beg + 1) & (out_que->max_size - 1);
    out_que->cnt -= 1;
    return ret;
}

void traverse_queue(const fixed_queue_t* que, void (*func)(void* const, int, void*), void* arg);
void init_queue_malloc(fixed_queue_t* const out_que, int max_size);
void cleanup_queue_free(fixed_queue_t* const out_que);

#endif /* __FIXED_QUEUE__H */
#ifndef __STATIC_QUEUE__H
#define __STATIC_QUEUE__H

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
    my_assert(!is_queue_empty(que));
    return que->pa[que->beg];
}

static inline void push_queue(fixed_queue_t* const que, void* tetro)
{
    my_assert(que->cnt < que->max_size);
    que->pa[que->end] = tetro;
    /* I know this way to be faster than the remainder operator. */
    if (++que->end == que->max_size) {
        que->end = 0;
    }
    que->cnt += 1;
}

static inline void* pop_queue(fixed_queue_t* const que)
{
    my_assert(!is_queue_empty(que));
    void* ret = que->pa[que->beg];
    if (++que->beg == que->max_size) {
        que->beg = 0;
    }
    que->cnt -= 1;
    return ret;
}

void traverse_queue(const fixed_queue_t* que, void (*func)(void* const, int, void*), void* arg);
void init_queue(fixed_queue_t* const out_que, int max_size);
void cleanup_queue(fixed_queue_t* const out_que);

#endif /* __STATIC_QUEUE__H */
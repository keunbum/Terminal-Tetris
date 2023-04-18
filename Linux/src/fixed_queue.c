#include <stdlib.h>

#include "fixed_queue.h"

void traverse_queue(const fixed_queue_t* que, void (*func)(void* const, int, void*), void* arg)
{
    size_t ptr = que->beg;
    for (int i = 0; i < (int)que->cnt; ++i) {
        func(que->pa[ptr], i, arg);
        if (++ptr == que->max_size) {
            ptr = 0;
        }
    }
}

void init_queue_malloc(fixed_queue_t* const out_que, int max_size)
{
    debug();
    
    out_que->max_size = max_size;
    out_que->beg = 0;
    out_que->end = 0;
    out_que->cnt = 0;
    out_que->pa = (void**)malloc(sizeof(void*) * out_que->max_size);
}

/* Not A Good Logic */
void cleanup_queue_free(fixed_queue_t* const out_que)
{
    // while (!is_queue_empty(out_que)) {
    //     void* cur = pop_queue(out_que);
    //     free(cur);
    //     cur = NULL;
    // }
    my_assert(out_que->pa != NULL);
    free(out_que->pa);
    out_que->pa = NULL;
}
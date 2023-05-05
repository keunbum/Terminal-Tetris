#ifndef __TETRIS_PLAY_SUBMODULE__H
#define __TETRIS_PLAY_SUBMODULE__H

#include <pthread.h>
#include <stdbool.h>

#include "debug.h"
#include "error_handling.h"

typedef void* (*thread_module_func_t)(void* arg);

typedef struct {
    pthread_t thread_id;
    bool is_detached;
    thread_module_func_t main_func;
    void* main_func_arg;
    void* retval;
} thread_module_t;

static inline void run_thread_module(thread_module_t* const out_module)
{
    int res = pthread_create(&out_module->thread_id, NULL, out_module->main_func, out_module->main_func_arg);
    if (res != 0) {
        handle_error_en("pthread_create() error", res);
    }
    if (out_module->is_detached) {
        res = pthread_detach(out_module->thread_id);
        if (res != 0) {
            handle_error_en("pthread_detach() error", res);
        }
    }
}

static inline void join_thread_module(thread_module_t* const out_module)
{
    if (out_module->is_detached) {
        return;
    }
    if (pthread_join(out_module->thread_id, &out_module->retval) != 0) {
        handle_error("pthread_join() error");
    }
}

void init_thread_module(thread_module_t* const out_module, bool is_detached, thread_module_func_t main_func, void* main_func_arg);
void cleanup_thread_module(thread_module_t* const out_module);

#endif /* __TETRIS_PLAY_SUBMODULE__H */

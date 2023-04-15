#ifndef __TETRIS_PLAY_SUBMODULE__H
#define __TETRIS_PLAY_SUBMODULE__H

#include <pthread.h>
#include <stdbool.h>

#include "debug.h"
#include "error_handling.h"

typedef void* (*tetris_play_submodule_func_t)(void* arg);

typedef struct {
    pthread_t pthread_id;
    tetris_play_submodule_func_t main_func;
    void* main_func_arg;
    bool is_detached;
    void* retval;
} tetris_play_submodule_t;

static inline void run_tetris_play_module_in_parallel(tetris_play_submodule_t* const out_game_play_module)
{
    debug();

    pthread_create(&out_game_play_module->pthread_id, NULL, out_game_play_module->main_func, out_game_play_module->main_func_arg);
    if (out_game_play_module->is_detached) {
        pthread_detach(out_game_play_module->pthread_id);
    }
}

static inline void join_tetris_play_module_in_parallel(tetris_play_submodule_t* const out_module)
{
    if (out_module->is_detached) {
        return;
    }
    if (pthread_join(out_module->pthread_id, &out_module->retval) != 0) {
        handle_error("pthread_join() error");
    }
}

#endif /* __TETRIS_PLAY_SUBMODULE__H */

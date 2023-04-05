#ifndef __TETRIS_PLAY_SUBMODULE__H
#define __TETRIS_PLAY_SUBMODULE__H

#include <pthread.h>
#include <stdbool.h>

typedef void* (*game_play_submodule_func_t)(void* arg);

typedef struct {
    pthread_t pthread_id;
    game_play_submodule_func_t main_func;
    void* main_func_arg;
    bool is_detached;
    void* retval;
} game_play_submodule_t;

#endif /* __TETRIS_PLAY_SUBMODULE__H */

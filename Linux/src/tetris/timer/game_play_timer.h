#ifndef __GAME_PLAY_TIMER__H
#define __GAME_PLAY_TIMER__H

#include <stdbool.h>

#include "realtime_timer.h"
#include "tetris/object/frame.h"

typedef void (*game_play_timer_routine_t)(void*);

typedef struct {
    game_play_timer_routine_t routine;
    void* arg;
} game_play_timer_module_t;

static inline void run_game_play_timer_module(const game_play_timer_module_t* module)
{
    module->routine(module->arg);
}

typedef struct {
    realtime_timer_t realtime_timer;
    game_play_timer_module_t before_module;
    game_play_timer_module_t main_module;
} game_play_timer_t;

void init_game_play_timer(game_play_timer_t* const out_game_play_timer, clockid_t clockid, int timersig, struct itimerspec its, game_play_timer_module_t before_module, game_play_timer_module_t main_module);
void cleanup_game_play_timer(game_play_timer_t* const out_game_play_timer);
void* run_game_play_timer(void* arg);

#endif /* __GAME_PLAY_TIMER__H */
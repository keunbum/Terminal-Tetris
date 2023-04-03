#ifndef __PLAY_MANAGER__H
#define __PLAY_MANAGER__H

#include "game/game_play/timer/timer_drawer.h"

typedef int play_mode_t;
typedef void* (*game_play_manager_module_t)(void*);

typedef struct {
    const play_mode_t mode;
    const int screen_start_pos_x_wprint;
    const int screen_start_pos_y_wprint;
    const int screen_height_wprint;
    const int ready_getset_go_sec;
    timer_drawer_t timer_drawer;
} game_play_manager_module_arg_t;

typedef struct {
    const char* name;
    game_play_manager_module_t module;
    void* module_arg;
} play_manager_t;

#endif /* __PLAY_MANAGER__H */
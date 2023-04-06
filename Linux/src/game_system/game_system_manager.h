#ifndef __GAME_SYSTEM_MANAGER__H
#define __GAME_SYSTEM_MANAGER__H

#include "tetris/scene/tetris_play_screen.h"

//#define CONSOLE_STDOUT_POS_X (TETRIS_PLAY_SINGLE_SCREEN_START_POS_X_WPRINT + GAME_PLAY_SINGLE_SCREEN_HEIGHT_WPRINT + 1)
//#define CONSOLE_STDOUT_POS_Y (0)

//#define CONSOLE_STDERR_POS_X (TETRIS_PLAY_SINGLE_SCREEN_START_POS_X_WPRINT)
//#define CONSOLE_STDERR_POS_Y (TETRIS_PLAY_SINGLE_SCREEN_START_POS_Y_WPRINT + GAME_PLAY_SINGLE_SCREEN_WIDTH_WPRINT + 5)

//typedef int play_mode_t;
typedef void* (*game_module_func_t)(void*);

typedef struct {
    const char* name;
    const game_module_func_t module;
    void* module_arg;
} game_module_t;

typedef enum {
    TETRIS_PLAY_MODE_SINGLE,
    TETRIS_PLAY_MODE_MULTI,
} tetris_play_mode_t;

void run_game_system_manager(void);

#endif /* __GAME_SYSTEM_MANAGER__H */
#ifndef __TETRIS_PLAY_MANAGER__H
#define __TETRIS_PLAY_MANAGER__H

#include "tetris/play/tetris_play_board.h"
#include "timer/timer_drawer.h"

typedef enum {
    TETRIS_PLAY_CMD_ERROR = -1,
    TETRIS_PLAY_CMD_EXIT_GAME = 0,
    TETRIS_PLAY_CMD_REGAME = 1,
} tetris_play_cmd_t;

typedef enum {
    TETRIS_PLAY_STATUS_ERROR = -1,
    TETRIS_PLAY_STATUS_GAME_OVER = 2,
} tetris_play_status_t;

#define TETRIS_PLAY_TIMER_POS_X_WPRINT (TETRIS_PLAY_SINGLE_SCREEN_START_POS_X_WPRINT + 2)
#define TETRIS_PLAY_TIMER_POS_Y_WPRINT (TETRIS_PLAY_BOARD_START_POS_Y_WPRINT + TETRIS_PLAY_BOARD_WIDTH / 2 - 1)

#define TETRIS_PLAY_TIMEINTERVAL_BEFORESTART_SEC (3)

typedef int play_mode_t;
typedef void* (*game_play_manager_module_t)(void*);

typedef struct {
    const play_mode_t mode;
    const int screen_start_pos_x_wprint;
    const int screen_start_pos_y_wprint;
    const int screen_height_wprint;
    const int ready_getset_go_sec;
    timer_drawer_t timer_drawer;
    game_board_t board;
} game_play_manager_module_arg_t;

typedef struct {
    const char* name;
    const game_play_manager_module_t module;
    void* module_arg;
} play_manager_t;

typedef enum {
    TETRIS_PLAY_MODE_SINGLE,
    TETRIS_PLAY_MODE_MULTI,
} tetris_play_mode_t;

#endif /* __TETRIS_PLAY_MANAGER__H */
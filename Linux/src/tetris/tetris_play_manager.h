#ifndef __TETRIS_PLAY_MANAGER__H
#define __TETRIS_PLAY_MANAGER__H

#include "game_system/game_system_manager.h"
#include "tetris/object/board.h"
#include "tetris/object/screen.h"
#include "tetris/object/tetromino.h"
#include "tetris/play/tetris_play_statistic.h"
#include "tetris/play/tetris_play_tetromino_generator.h"
#include "tetris_play_submodule.h"
#include "timer/timer_drawer.h"

#define TETRIS_PLAY_TIMER_POS_X_WPRINT (TETRIS_PLAY_SINGLE_SCREEN_POS_X_WPRINT + 2)
#define TETRIS_PLAY_TIMER_POS_Y_WPRINT (TETRIS_PLAY_BOARD_POS_Y_WPRINT + TETRIS_PLAY_BOARD_WIDTH / 2 - 2)

#define TETRIS_PLAY_TIMEINTERVAL_BEFORESTART_SEC (3)

typedef enum {
    TETRIS_PLAY_STATUS_ERROR = -1,
    TETRIS_PLAY_STATUS_GAMEOVER,
    TETRIS_PLAY_STATUS_RUNNING,
    TETRIS_PLAY_STATUS_PAUSE,
} tetris_play_status_t;

typedef struct {
} tetris_play_world_t;

typedef struct {
    const int screen_start_pos_x_wprint;
    const int screen_start_pos_y_wprint;
    const int screen_height_wprint;
    const int ready_getset_go_sec;

    tetris_play_mode_t play_mode;
    tetris_play_status_t status;
    game_time_t game_delta_time;

    screen_t screen;
    board_t board;
    tetris_play_statistic_t stat;
    tetromino_generator_t gen;
    tetromino_t tetromino;
    tetromino_t prev_tetromino;
    timer_drawer_t timer_drawer;
#define TETRIS_PLAY_SUBMODULE_NUM (3)
    game_play_submodule_t sub_modules[TETRIS_PLAY_SUBMODULE_NUM];
} tetris_play_manager_t;

#endif /* __TETRIS_PLAY_MANAGER__H */
#ifndef __TETRIS_PLAY_MANAGER__H
#define __TETRIS_PLAY_MANAGER__H

#include "game_system/game_system_manager.h"
#include "tetris/object/board.h"
#include "tetris/object/screen.h"
#include "tetris/object/tetromino.h"
#include "tetris/object/frame.h"
#include "tetris/play/tetris_play_tetromino_statistic.h"
#include "tetris/play/tetris_play_tetromino_generator.h"
#include "tetris/play/tetris_play_tetromino_manager.h"
#include "tetris_play_submodule.h"
#include "timer/timer_drawer.h"
#include "terminal.h"

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

#define TETRIS_PLAY_SUBMODULE_NUM (3)

typedef struct {
    const int ready_getset_go_sec;
    const int tetromino_queue_max_size;
    const pos_int_t pos_wprint;

    tetris_play_mode_t play_mode;
    tetris_play_status_t status;
    game_time_t game_delta_time;

    frame_t screen_frame;
    board_t board;
    tetromino_manager_t tetro_man;
    terminal_t terminal;
    
    timer_drawer_t timer_drawer;
    tetris_play_submodule_t sub_modules[TETRIS_PLAY_SUBMODULE_NUM];
} tetris_play_manager_t;

#endif /* __TETRIS_PLAY_MANAGER__H */
#ifndef __TETRIS_PLAY_MANAGER__H
#define __TETRIS_PLAY_MANAGER__H

#include "device_input.h"
#include "game_system/game_system_manager.h"
#include "terminal.h"
#include "tetris/object/frame.h"
#include "tetris/object/matrix.h"
#include "tetris/object/tetromino.h"
#include "tetris/play/tetris_play_tetromino_generator.h"
#include "tetris/play/tetris_play_tetromino_manager.h"
#include "tetris/play/tetris_play_tetromino_statistic.h"
#include "tetris/timer/tetris_play_timer.h"
#include "thread_module.h"

#define TETRIS_PLAY_TIMER_POS_X_WPRINT (TETRIS_PLAY_SINGLE_SCREEN_POS_X_WPRINT + 2)
#define TETRIS_PLAY_TIMER_POS_Y_WPRINT (TETRIS_PLAY_MATRIX_POS_Y_WPRINT + TETRIS_PLAY_MATRIX_WIDTH / 2 - 1)

#define TETRIS_PLAY_TIMEINTERVAL_BEFORESTART_SEC (3)

typedef enum {
    TETRIS_PLAY_STATUS_ERROR = -1,
    TETRIS_PLAY_STATUS_GAMEOVER,
    TETRIS_PLAY_STATUS_RUNNING,
    TETRIS_PLAY_STATUS_PAUSE,
} tetris_play_status_t;

#define TETRIS_PLAY_SUBMODULE_NUM (2)

typedef struct {
    const int ready_getset_go_sec;
    const int tetromino_next_queue_max_size;
    const pos_int_t screen_pos_wprint;

    tetris_play_mode_t play_mode;
    tetris_play_status_t status;
    game_time_t game_delta_time;

    frame_t screen_frame;
    tetromino_manager_t tetro_man;
    terminal_t terminal;
    device_input_t input;

    tetris_play_timer_t tetris_play_timer;
    thread_module_t sub_modules[TETRIS_PLAY_SUBMODULE_NUM];
} tetris_play_manager_t;

typedef enum {
    TETRIS_PLAY_MANUAL_KEYBOARD,
    TETRIS_PLAY_MANUAL_CONTROLLER,
} tetris_play_manual_t;

void wdraw_show_manual(const tetris_play_manager_t* play_manager, tetris_play_manual_t manual);

#endif /* __TETRIS_PLAY_MANAGER__H */
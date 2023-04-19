#ifndef __TETRIS_PLAY_TETROMINO_MANAGER__H
#define __TETRIS_PLAY_TETROMINO_MANAGER__H

#include <stdlib.h>

#include "fixed_queue.h"
#include "pthread_macro.h"
#include "tetris/object/board.h"
#include "tetris/object/frame.h"
#include "tetris/play/tetris_play_tetromino_statistic.h"
#include "tetris/play/tetris_play_update_tetromino_status.h"
#include "tetris/scene/tetris_play_screen.h"
#include "tetris_play_tetromino_generator.h"
#include "tetris/tetris_play_fps.h"

#define TETROMINO_MANAGER_QUEUE_MAX_SIZE (5)

#define TETRIS_PLAY_TETROMINO_MANAGER_POS_X_WPRINT (TETRIS_PLAY_SINGLE_SCREEN_POS_X_WPRINT + 6)
#define TETRIS_PLAY_TETROMINO_MANAGER_POS_Y_WPRINT (TETRIS_PLAY_SINGLE_SCREEN_POS_Y_WPRINT + (TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT + TETRIS_PLAY_BOARD_WIDTH_WPRINT) / 2 + 2)

#define TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_HEIGHT_WPRINT (4 * TETROMINO_MANAGER_QUEUE_MAX_SIZE + 2)
#define TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_WIDTH_WPRINT ((TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT - TETRIS_PLAY_BOARD_WIDTH_WPRINT) / 2 - 5)

typedef pthread_spinlock_t tetromino_manager_lock_t;

typedef struct {
    pos_int_t pos_wprint;

    bool is_swaped;
    game_time_t unit_velocity;
    game_time_t tetromino_init_velocity;
    tetromino_t* tetro_main;
    tetromino_t* tetro_hold;

    tetromino_generator_t tetro_gen;
    tetris_play_statistic_t stat;
    fixed_queue_t que;
    frame_t frame;

    tetromino_manager_lock_t lock;
} tetromino_manager_t;

void init_tetromino_manager(tetromino_manager_t* const out_man, int max_size);
void cleanup_tetromino_manager_free(tetromino_manager_t* const out_man);
tetromino_try_status_t update_tetromino_manager(tetromino_manager_t* const out_man, board_t* const out_board, game_time_t delta_time);
void wdraw_tetromino_manager(const tetromino_manager_t* man);
// void swap_tetromino_hold(tetromino_manager_t* const out_man);

#endif /* __TETRIS_PLAY_TETROMINO_MANAGER__H */
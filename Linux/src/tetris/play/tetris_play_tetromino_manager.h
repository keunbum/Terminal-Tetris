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
#include "tetris_play_fps.h"
#include "tetris_play_tetromino_generator.h"
#include "tetris_play_tetromino_silhouette.h"

#define TETROMINO_MANAGER_QUEUE_MAX_SIZE (8)
#define TETROMINO_MANAGER_QUEUE_FULL_SIZE (6)

#define TETRIS_PLAY_TETROMINO_MANAGER_POS_X_WPRINT (TETRIS_PLAY_SINGLE_SCREEN_POS_X_WPRINT + 7)
#define TETRIS_PLAY_TETROMINO_MANAGER_POS_Y_WPRINT (TETRIS_PLAY_SINGLE_SCREEN_POS_Y_WPRINT + (TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT + TETRIS_PLAY_BOARD_WIDTH_WPRINT) / 2 + 2)

#define TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_HEIGHT_WPRINT (4 * TETROMINO_MANAGER_QUEUE_FULL_SIZE + 2)
#define TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_WIDTH_WPRINT ((TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT - TETRIS_PLAY_BOARD_WIDTH_WPRINT) / 2 - 5)

#define TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_POS_X (TETRIS_PLAY_SINGLE_SCREEN_POS_X + 3)
#define TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_POS_Y (TETRIS_PLAY_SINGLE_SCREEN_POS_Y + 5)

#define TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_HEIGHT_WPRINT (4)
#define TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_WIDTH_WPRINT (6 * 2)

#define SPEED_DRAW_POS_X_WPRINT (3)
#define SPEED_DRAW_POS_Y_WPRINT (50)
#define LINES_DRAW_POS_X_WPRINT (4)
#define LINES_DRAW_POS_Y_WPRINT (50)

typedef pthread_mutex_t tetromino_manager_lock_t;

typedef struct {
    pos_int_t next_pos_wprint;
    pos_int_t hold_pos;

    bool is_swaped_once;
    game_time_t unit_velocity;
    game_time_t tetromino_init_velocity;
    tetromino_t* tetro_main;
    tetromino_t* tetro_hold;
    tetromino_t tetro_silhou;
    board_t board;

    tetromino_generator_t tetro_gen;
    tetris_play_statistic_t stat;
    fixed_queue_t que;
    frame_t next_frame;
    frame_t hold_frame;

    tetromino_manager_lock_t lock;
} tetromino_manager_t;

static inline void init_tetromino_manager_lock(tetromino_manager_t* const out_tetromino_manager)
{
    init_lock(out_tetromino_manager->lock);
}

static inline void lock_tetromino_manager(tetromino_manager_t* const out_tetromino_manager)
{
    debug();

    check_lock(out_tetromino_manager->lock);
}

static inline void unlock_tetromino_manager(tetromino_manager_t* const out_tetromino_manager)
{
    debug();

    check_unlock(out_tetromino_manager->lock);
}

static inline void cleanup_tetromino_manager_lock(tetromino_manager_t* const out_tetromino_manager)
{
    cleanup_lock(out_tetromino_manager->lock);
}

static inline void cleanup_tetromino_ontheground(tetromino_manager_t* const out_man)
{
    cleanup_tetromino_free(out_man->tetro_main);
    out_man->tetro_main = NULL;
    cleanup_tetromino_silhouette(&out_man->tetro_silhou);
}

static inline void wdraw_tetromino_speed(const tetromino_manager_t* man)
{
    // debug();

    const int pos_x_wprint = SPEED_DRAW_POS_X_WPRINT;
    const int pos_y_wprint = SPEED_DRAW_POS_Y_WPRINT;
    wprintf_at_r(pos_x_wprint, pos_y_wprint, L"SPEED: %-4.2lf", man->tetromino_init_velocity);
}

static inline void update_tetromino_manager_info(tetromino_manager_t* const out_man, int lines)
{
    out_man->is_swaped_once = false;
    out_man->tetromino_init_velocity += lines * out_man->unit_velocity;
    wdraw_tetromino_speed(out_man);
}

void init_tetromino_manager(tetromino_manager_t* const out_man, int max_size);
void cleanup_tetromino_manager_free(tetromino_manager_t* const out_man);
tetromino_status_t update_tetromino_manager(tetromino_manager_t* const out_man, game_time_t delta_time);
void wdraw_tetromino_manager(const tetromino_manager_t* man);
tetromino_status_t try_swap_tetromino_hold(tetromino_manager_t* const out_man);

#endif /* __TETRIS_PLAY_TETROMINO_MANAGER__H */
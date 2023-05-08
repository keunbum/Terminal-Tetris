#ifndef __TETRIS_PLAY_TETROMINO_MANAGER__H
#define __TETRIS_PLAY_TETROMINO_MANAGER__H

#include <stdlib.h>

#include "fixed_queue.h"
#include "pthread_macro.h"
#include "tetris/object/matrix.h"
#include "tetris/object/frame.h"
#include "tetris/play/tetris_play_tetromino_statistic.h"
#include "tetris/play/tetris_play_update_tetromino_in_play_status.h"
#include "tetris/scene/tetris_play_screen.h"
#include "tetris_play_fps.h"
#include "tetris_play_tetromino_generator.h"
#include "tetris_play_ghost_piece.h"

#define TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_MAX_SIZE (8)
#define TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FULL_SIZE (6)

#define TETRIS_PLAY_TETROMINO_MANAGER_POS_X_WPRINT (TETRIS_PLAY_SINGLE_SCREEN_POS_X_WPRINT + 7)
#define TETRIS_PLAY_TETROMINO_MANAGER_POS_Y_WPRINT (TETRIS_PLAY_SINGLE_SCREEN_POS_Y_WPRINT + (TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT + TETRIS_PLAY_MATRIX_WIDTH_WPRINT) / 2 + 2)

#define TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_HEIGHT_WPRINT (4 * TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FULL_SIZE + 2)
#define TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_WIDTH_WPRINT ((TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT - TETRIS_PLAY_MATRIX_WIDTH_WPRINT) / 2 - 5)

#define TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_POS_X (TETRIS_PLAY_SINGLE_SCREEN_POS_X + 3)
#define TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_POS_Y (TETRIS_PLAY_SINGLE_SCREEN_POS_Y + 5)
#define TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_HEIGHT_WPRINT (4)
#define TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_WIDTH_WPRINT (6 * 2)

#define TETROMINO_IN_PLAY_SPEED_DRAW_POS_X_WPRINT (3)
#define TETROMINO_IN_PLAY_SPEED_DRAW_POS_Y_WPRINT (50)

#define LINES_DRAW_POS_X_WPRINT (4)
#define LINES_DRAW_POS_Y_WPRINT (50)

typedef pthread_mutex_t tetromino_manager_lock_t;

typedef struct {
    pos_int_t next_queue_pos_wprint;
    pos_int_t hold_piece_pos;

    game_time_t tetromino_in_play_velocity_rate_of_change;
    game_time_t tetromino_in_play_velocity;
    bool is_swaped_once;
    tetromino_t* tetromino_in_play;
    tetromino_t* tetromino_hold;
    tetromino_t ghost_piece; // name from https://tetris.fandom.com/wiki/Ghost_piece
    matrix_t matrix;

    tetromino_generator_t tetro_gen;
    tetris_play_statistic_t stat;
    fixed_queue_t next_queue;
    frame_t next_queue_frame;
    frame_t hold_frame;
} tetromino_manager_t;

static inline void cleanup_lockdown_tetromino_in_play(tetromino_manager_t* const out_man)
{
    cleanup_tetromino_free(out_man->tetromino_in_play);
    out_man->tetromino_in_play = NULL;
    cleanup_ghost_piece(&out_man->ghost_piece);
}

static inline void wdraw_tetromino_in_play_speed(const tetromino_manager_t* man)
{
    wprintf_at_r(TETROMINO_IN_PLAY_SPEED_DRAW_POS_X_WPRINT, TETROMINO_IN_PLAY_SPEED_DRAW_POS_Y_WPRINT, L"SPEED: %-4.2lf", man->tetromino_in_play_velocity);
}

static inline void update_tetromino_manager_after_lockdown(tetromino_manager_t* const out_man, int lines)
{
    out_man->is_swaped_once = false;
    out_man->tetromino_in_play_velocity += lines * out_man->tetromino_in_play_velocity_rate_of_change;
    wdraw_tetromino_in_play_speed(out_man);
}

void init_tetromino_manager(tetromino_manager_t* const out_man, int max_size);
void cleanup_tetromino_manager_free(tetromino_manager_t* const out_man);
tetromino_in_play_status_t update_tetromino_manager(tetromino_manager_t* const out_man, game_time_t delta_time);
void wdraw_tetromino_manager(const tetromino_manager_t* man);
tetromino_in_play_status_t try_hold_tetromino_in_play(tetromino_manager_t* const out_man);

#endif /* __TETRIS_PLAY_TETROMINO_MANAGER__H */
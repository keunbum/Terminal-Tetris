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
#include "tetris_play_ghost_piece.h"

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

    game_time_t unit_velocity;
    game_time_t tetromino_init_velocity;
    bool is_swaped_once;
    tetromino_t* main_piece;
    tetromino_t* hold_piece;
    tetromino_t ghost_piece; // name from https://tetris.fandom.com/wiki/Ghost_piece
    board_t board;

    tetromino_generator_t tetro_gen;
    tetris_play_statistic_t stat;
    fixed_queue_t que;
    frame_t next_frame;
    frame_t hold_frame;
} tetromino_manager_t;

static inline void cleanup_tetromino_ontheground(tetromino_manager_t* const out_man)
{
    cleanup_tetromino_free(out_man->main_piece);
    out_man->main_piece = NULL;
    cleanup_ghost_piece(&out_man->ghost_piece);
}

static inline void wdraw_tetromino_speed(const tetromino_manager_t* man)
{
    wprintf_at_r(SPEED_DRAW_POS_X_WPRINT, SPEED_DRAW_POS_Y_WPRINT, L"SPEED: %-4.2lf", man->tetromino_init_velocity);
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
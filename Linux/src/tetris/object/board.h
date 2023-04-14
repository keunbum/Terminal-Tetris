#ifndef __TETRIS_PLAY_BOARD__H
#define __TETRIS_PLAY_BOARD__H

#include <pthread.h>
#include <wchar.h>

#include "block_code.h"
#include "tetris/object/board.h"
#include "tetris/object/tetromino.h"
#include "tetris/scene/tetris_play_screen.h"
#include "tetris_play_object.h"

#define TETRIS_PLAY_BOARD_HEIGHT (22)
#define TETRIS_PLAY_BOARD_WIDTH (12)
#define TETRIS_PLAY_BOARD_HEIGHT_WPRINT (TETRIS_PLAY_BOARD_HEIGHT)
#define TETRIS_PLAY_BOARD_WIDTH_WPRINT (2 * TETRIS_PLAY_BOARD_WIDTH)

#define TETRIS_PLAY_BOARD_POS_X_WPRINT \
    (TETRIS_PLAY_SINGLE_SCREEN_POS_X_WPRINT + (TETRIS_PLAY_SINGLE_SCREEN_HEIGHT_WPRINT - TETRIS_PLAY_BOARD_HEIGHT_WPRINT) / 2 + 4)
#define TETRIS_PLAY_BOARD_POS_Y_WPRINT \
    (TETRIS_PLAY_SINGLE_SCREEN_POS_Y_WPRINT + (TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT - TETRIS_PLAY_BOARD_WIDTH_WPRINT) / 2 + 0)
#define TETRIS_PLAY_BOARD_POS_X TETRIS_PLAY_BOARD_POS_X_WPRINT
#define TETRIS_PLAY_BOARD_POS_Y (TETRIS_PLAY_BOARD_POS_Y_WPRINT / 2)

#define TETRIS_PLAY_BOARD_GRID_ELEMENT_DEFAULT (0)

#define BOARD_FRAME_HEIGHT (TETRIS_PLAY_BOARD_HEIGHT + 2)
#define BOARD_FRAME_WIDTH (TETRIS_PLAY_BOARD_WIDTH + 2)

#define BOARD_FRAME_POS_X (TETRIS_PLAY_BOARD_POS_X - 1)
#define BOARD_FRAME_POS_Y (TETRIS_PLAY_BOARD_POS_Y - 1)
#define BOARD_FRAME_POS_X_WPRINT (TETRIS_PLAY_BOARD_POS_X_WPRINT - 1)
#define BOARD_FRAME_POS_Y_WPRINT (TETRIS_PLAY_BOARD_POS_Y_WPRINT - 2)

/* may be changed. */
typedef tetromino_id_t board_grid_element_t;
typedef pthread_spinlock_t board_lock_t;

extern board_lock_t g_board_lock;

typedef struct {
    const wchar_t game_board_unit_matrix_corner_top_left;
    const wchar_t game_board_unit_matrix_corner_top_right;
    const wchar_t game_board_unit_matrix_corner_bot_left;
    const wchar_t game_board_unit_matrix_corner_bot_right;
    const wchar_t game_board_unit_matrix_ver_line;
    const wchar_t game_board_unit_matrix_hor_line;
    const wchar_t game_board_unit_matrix_inner;

    const int height;
    const int width;
    const int height_wprint;
    const int width_wprint;
    const int frame_height;
    const int frame_width;

    const pos_t pos;
    const pos_t pos_wprint;
    const pos_t frame_pos;
    const pos_t frame_pos_wprint;
    board_grid_element_t grid[TETRIS_PLAY_BOARD_HEIGHT][TETRIS_PLAY_BOARD_WIDTH];
    block_code_t code_grid[TETRIS_PLAY_BOARD_HEIGHT][TETRIS_PLAY_BOARD_WIDTH];
    updatable_func_t update;
    drawable_func_t draw;
} board_t;

typedef board_t board_t;

#define init_board_lock() func_check_error(pthread_spin_init, &g_board_lock, PTHREAD_PROCESS_PRIVATE)
#define board_lock() func_check_error(pthread_spin_lock, &g_board_lock)
#define board_unlock() func_check_error(pthread_spin_unlock, &g_board_lock)
#define cleanup_board_lock() func_check_error(pthread_spin_destroy, &g_board_lock)

void init_board(board_t* const board, board_grid_element_t val);
void wdraw_board(const board_t* board);

#endif /* __TETRIS_PLAY_BOARD__H */
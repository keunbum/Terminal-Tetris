#ifndef __TETRIS_PLAY_BOARD__H
#define __TETRIS_PLAY_BOARD__H

#include <pthread.h>
#include <wchar.h>

#include "block.h"
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

// #define TETRIS_PLAY_BOARD_GRID_ELEMENT_DEFAULT (0)

#define BOARD_FRAME_HEIGHT (TETRIS_PLAY_BOARD_HEIGHT + 2)
#define BOARD_FRAME_WIDTH (TETRIS_PLAY_BOARD_WIDTH + 2)

#define BOARD_FRAME_POS_X (TETRIS_PLAY_BOARD_POS_X - 1)
#define BOARD_FRAME_POS_Y (TETRIS_PLAY_BOARD_POS_Y - 1)
#define BOARD_FRAME_POS_X_WPRINT (TETRIS_PLAY_BOARD_POS_X_WPRINT - 1)
#define BOARD_FRAME_POS_Y_WPRINT (TETRIS_PLAY_BOARD_POS_Y_WPRINT - 2)

/* may be changed. */
typedef pthread_spinlock_t board_lock_t;

extern board_lock_t g_board_lock;

typedef block_t row_t[TETRIS_PLAY_BOARD_WIDTH];

typedef struct {
    const wchar_t block_corner_top_left;
    const wchar_t block_corner_top_right;
    const wchar_t block_corner_bot_left;
    const wchar_t block_corner_bot_right;
    const wchar_t block_ver_line;
    const wchar_t block_hor_line;
    const wchar_t block_inner;

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
    row_t grid[TETRIS_PLAY_BOARD_HEIGHT];
    // block_t grid[TETRIS_PLAY_BOARD_HEIGHT][TETRIS_PLAY_BOARD_WIDTH];
    // updatable_func_t update;
    // drawable_func_t draw;
} board_t;

typedef board_t board_t;

#define init_board_lock() func_check_error(pthread_spin_init, &g_board_lock, PTHREAD_PROCESS_PRIVATE)
#define board_lock() func_check_error(pthread_spin_lock, &g_board_lock)
#define board_unlock() func_check_error(pthread_spin_unlock, &g_board_lock)
#define cleanup_board_lock() func_check_error(pthread_spin_destroy, &g_board_lock)

void init_board(board_t* const out_board);
void wdraw_board(const board_t* board);

static inline const row_t* get_grid(const board_t* board)
{
    return board->grid;
}

static inline const block_t* get_board_grid_block(const board_t* board, int i, int j)
{
    board_lock();
    const block_t* ret = get_grid(board)[i] + j;
    board_unlock();
    return ret;
}

static inline void set_board_grid_block(board_t* const out_board, int i, int j, block_t block)
{
    board_lock();
    set_block(out_board->grid[i] + j, block);
    board_unlock();
}

#endif /* __TETRIS_PLAY_BOARD__H */
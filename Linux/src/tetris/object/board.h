#ifndef __TETRIS_PLAY_BOARD__H
#define __TETRIS_PLAY_BOARD__H

#include <pthread.h>
#include <wchar.h>

#include "block.h"
#include "tetris/object/board.h"
#include "tetris/object/tetromino.h"
#include "tetris/scene/tetris_play_screen.h"
#include "tetris_play_object.h"
#include "pthread_macro.h"

#define TETRIS_PLAY_BOARD_INNER_HEIGHT (20)
#define TETRIS_PLAY_BOARD_INNER_WIDTH (10)

#define TETRIS_PLAY_BOARD_HEIGHT (TETRIS_PLAY_BOARD_INNER_HEIGHT + 10)
#define TETRIS_PLAY_BOARD_WIDTH (TETRIS_PLAY_BOARD_INNER_WIDTH + 2)
#define TETRIS_PLAY_BOARD_HEIGHT_WPRINT (TETRIS_PLAY_BOARD_HEIGHT)
#define TETRIS_PLAY_BOARD_WIDTH_WPRINT (2 * TETRIS_PLAY_BOARD_WIDTH)

#define TETRIS_PLAY_BOARD_POS_X_WPRINT \
    (TETRIS_PLAY_SINGLE_SCREEN_POS_X_WPRINT + (TETRIS_PLAY_SINGLE_SCREEN_HEIGHT_WPRINT - TETRIS_PLAY_BOARD_HEIGHT_WPRINT) / 2 + 4)
#define TETRIS_PLAY_BOARD_POS_Y_WPRINT \
    (TETRIS_PLAY_SINGLE_SCREEN_POS_Y_WPRINT + (TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT - TETRIS_PLAY_BOARD_WIDTH_WPRINT) / 2 + 0)
#define TETRIS_PLAY_BOARD_POS_X TETRIS_PLAY_BOARD_POS_X_WPRINT
#define TETRIS_PLAY_BOARD_POS_Y (TETRIS_PLAY_BOARD_POS_Y_WPRINT / 2)

#define TETRIS_PLAY_SKYLINE_POS_X (TETRIS_PLAY_BOARD_POS_X + (TETRIS_PLAY_BOARD_HEIGHT - 2 - 20))

#define BOARD_FRAME_HEIGHT (TETRIS_PLAY_BOARD_HEIGHT + 2)
#define BOARD_FRAME_WIDTH (TETRIS_PLAY_BOARD_WIDTH + 2)

#define BOARD_FRAME_POS_X (TETRIS_PLAY_BOARD_POS_X - 1)
#define BOARD_FRAME_POS_Y (TETRIS_PLAY_BOARD_POS_Y - 1)
#define BOARD_FRAME_POS_X_WPRINT (TETRIS_PLAY_BOARD_POS_X_WPRINT - 1)
#define BOARD_FRAME_POS_Y_WPRINT (TETRIS_PLAY_BOARD_POS_Y_WPRINT - 2)

typedef pthread_spinlock_t board_lock_t;

typedef block_t row_t[TETRIS_PLAY_BOARD_WIDTH];
typedef struct {
    const wchar_t block_corner_top_left;
    const wchar_t block_corner_top_right;
    const wchar_t block_corner_bot_left;
    const wchar_t block_corner_bot_right;
    const wchar_t block_ver_line;
    const wchar_t block_hor_line;
    const wchar_t block_inner;
    const wchar_t block_skyline;
    const wchar_t block_sky;

    const pos_int_t pos;
    const pos_int_t pos_wprint;
    const pos_int_t frame_pos;
    const pos_int_t frame_pos_wprint;
    const pos_int_t skyline_pos;

    const int height;
    const int width;
    const int height_wprint;
    const int width_wprint;
    const int frame_height;
    const int frame_width;
    const int skyline;

    row_t grid[TETRIS_PLAY_BOARD_HEIGHT];

    board_lock_t lock;
} board_t;

typedef board_t board_t;

#define traverse_inner_row(i, board) for (int i = board->height - 2; i > board->skyline_pos.x - board->pos.x; --i)
#define traverse_inner_col(j, board) for (int j = 1; j <= board->width - 2; ++j)

static inline void init_board_lock(board_t* const out_board)
{
    init_lock(out_board->lock);
}

static inline void lock_board(board_t* const out_board)
{
    debug();

    check_lock(out_board->lock);
}

static inline void unlock_board(board_t* const out_board)
{
    debug();
    
    check_unlock(out_board->lock);
}

static inline void cleanup_board_lock(board_t* const out_board)
{
    cleanup_lock(out_board->lock);
}

static inline const row_t* get_grid(const board_t* board)
{
    return board->grid;
}

static inline const block_t* get_board_grid_block(const board_t* board, int i, int j)
{
    const block_t* ret = get_grid(board)[i] + j;
    return ret;
}

static inline void set_board_grid_block(board_t* const out_board, int i, int j, block_t block)
{
    set_block(out_board->grid[i] + j, block);
}

void init_board(board_t* const out_board);
void cleanup_board(board_t* const out_board);
void wdraw_board(const board_t* board);

#endif /* __TETRIS_PLAY_BOARD__H */
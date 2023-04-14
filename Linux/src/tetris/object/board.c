#include "board.h"
#include "debug.h"
#include "draw/draw_tool.h"

board_lock_t g_board_lock;

static inline void init_board_block(board_t* const out_board, int i, int j, block_nature_t nature, block_wprint_t wprint)
{
    init_block(out_board->grid[i] + j, nature, wprint);
}

void init_board(board_t* const out_board)
{
    debug();

    init_board_block(out_board, 0, 0, BLOCK_NATURE_FULL, out_board->block_corner_top_left);
    init_board_block(out_board, 0, out_board->width - 1, BLOCK_NATURE_FULL, out_board->block_corner_top_right);
    init_board_block(out_board, out_board->height - 1, 0, BLOCK_NATURE_FULL, out_board->block_corner_bot_left);
    init_board_block(out_board, out_board->height - 1, out_board->width - 1, BLOCK_NATURE_FULL, out_board->block_corner_bot_right);

    for (int i = 0; i < out_board->height; ++i) {
        if (i == 0 || i == out_board->height - 1) {
            for (int j = 1; j < out_board->width - 1; ++j) {
                init_board_block(out_board, i, j, BLOCK_NATURE_FULL, out_board->block_hor_line);
            }
        } else {
            for (int j = 0; j < out_board->width; ++j) {
                if (j == 0 || j == out_board->width - 1) {
                    init_board_block(out_board, i, j, BLOCK_NATURE_FULL, out_board->block_ver_line);
                } else {
                    init_board_block(out_board, i, j, BLOCK_NATURE_EMPTY, out_board->block_inner);
                }
            }
        }
    }
}

void wdraw_board(const board_t* board)
{
    cursor_lock();
    wgotoxy((int)board->pos_wprint.x, (int)board->pos_wprint.y);
    for (int i = 0; i < board->height; ++i) {
        for (int j = 0; j < board->width; ++j) {
            get_block_wprint(board->grid[i] + j);
        }
        wprintf(L"\e[1B\e[%dD", board->width_wprint);
    }
    cursor_unlock();
}
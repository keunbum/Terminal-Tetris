#include "board.h"
#include "debug.h"
#include "draw/draw_tool.h"

static inline void set_board_block(board_t* const out_board, int i, int j, block_t block)
{
    set_block(out_board->grid[i] + j, block);
}

static inline void set_board_block_each(board_t* const out_board, int i, int j, block_nature_t nature, block_wprint_t wprint)
{
    set_block_each(out_board->grid[i] + j, nature, wprint);
}

void init_board(board_t* const out_board)
{
    debug();

    init_board_lock(out_board);

    set_board_block_each(out_board, 0, 0, BLOCK_NATURE_FULL, out_board->block_corner_top_left);
    set_board_block_each(out_board, 0, out_board->width - 1, BLOCK_NATURE_FULL, out_board->block_corner_top_right);
    set_board_block_each(out_board, out_board->height - 1, 0, BLOCK_NATURE_FULL, out_board->block_corner_bot_left);
    set_board_block_each(out_board, out_board->height - 1, out_board->width - 1, BLOCK_NATURE_FULL, out_board->block_corner_bot_right);

    for (int i = 0; i < out_board->height; ++i) {
        if (i == 0 || i == out_board->height - 1) {
            for (int j = 1; j < out_board->width - 1; ++j) {
                set_board_block_each(out_board, i, j, BLOCK_NATURE_FULL, out_board->block_hor_line);
            }
        } else {
            for (int j = 0; j < out_board->width; ++j) {
                if (j == 0 || j == out_board->width - 1) {
                    set_board_block_each(out_board, i, j, BLOCK_NATURE_FULL, 
                    (i == TETRIS_PLAY_SKY_LINE_POS_X - TETRIS_PLAY_BOARD_POS_X) ? out_board->block_skyline : out_board->block_ver_line);
                } else {
                    set_board_block_each(out_board, i, j, BLOCK_NATURE_EMPTY, out_board->block_inner);
                }
            }
        }
    }

    ewprintf("board's pos: (%d, %d), poswprint: (%d, %d)\n", (int)out_board->pos.x, (int)out_board->pos.y, (int)out_board->pos_wprint.x, (int)out_board->pos_wprint.y);
}

void cleanup_board(board_t* const out_board)
{
    cleanup_board_lock(out_board);
}

void wdraw_board(const board_t* board)
{
    debug();

    my_assert(board != NULL);

    cursor_lock();
    wgotoxy((int)board->pos_wprint.x, (int)board->pos_wprint.y);
    for (int i = 0; i < board->height; ++i) {
        for (int j = 0; j < board->width; ++j) {
            wdraw_unit_matrix(get_block_wprint(board->grid[i] + j));
        }
        wprintf(L"\e[1B\e[%dD", board->width_wprint);
    }
    cursor_unlock();
}
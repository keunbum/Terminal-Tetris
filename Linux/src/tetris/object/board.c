#include "board.h"
#include "debug.h"
#include "draw/draw_tool.h"

static inline void set_board_block_each(board_t* const out_board, int i, int j, block_nature_t nature, block_wprint_t wprint)
{
    set_block_each(out_board->grid[i] + j, nature, wprint);
}

void init_board(board_t* const out_board)
{
    debug();

    set_board_block_each(out_board, 0, 0, BLOCK_NATURE_FULL, out_board->block_corner_top_left);
    set_board_block_each(out_board, 0, out_board->width - 1, BLOCK_NATURE_FULL, out_board->block_corner_top_right);
    set_board_block_each(out_board, out_board->height - 1, 0, BLOCK_NATURE_FULL, out_board->block_corner_bot_left);
    set_board_block_each(out_board, out_board->height - 1, out_board->width - 1, BLOCK_NATURE_FULL, out_board->block_corner_bot_right);

    // for (int i = 0; i < out_board->height; ++i) {
    //     if (i == 0 || i == out_board->height - 1) {
    //         for (int j = 1; j < out_board->width - 1; ++j) {
    //             set_board_block_each(out_board, i, j, BLOCK_NATURE_FULL, out_board->block_hor_line);
    //         }
    //     } else {
    //         for (int j = 0; j < out_board->width; ++j) {
    //             if (j == 0 || j == out_board->width - 1) {
    //                 set_board_block_each(out_board, i, j, BLOCK_NATURE_FULL, out_board->block_ver_line);
    //             } else {
    //                 int sky_line_i = out_board->skyline_pos.x - TETRIS_PLAY_BOARD_POS_X;
    //                 block_wprint_t block_wprint;
    //                 if (i == sky_line_i) {
    //                     block_wprint = out_board->block_skyline;
    //                 } else {
    //                     block_wprint = out_board->block_inner;
    //                 }
    //                 set_board_block_each(out_board, i, j, BLOCK_NATURE_EMPTY, block_wprint);
    //             }
    //         }
    //     }
    // }

    for (int i = 0; i < out_board->height; ++i) {
        const int sky_line_i = out_board->skyline_pos.x - TETRIS_PLAY_BOARD_POS_X;
        if (i == 0 || i == out_board->height - 1) {
            for (int j = 1; j < out_board->width - 1; ++j) {
                set_board_block_each(out_board, i, j, i == sky_line_i ? BLOCK_NATURE_EMPTY : BLOCK_NATURE_FULL, out_board->block_hor_line);
            }
        } else {
            for (int j = 0; j < out_board->width; ++j) {
                if (j == 0 || j == out_board->width - 1) {
                    set_board_block_each(out_board, i, j, BLOCK_NATURE_FULL, out_board->block_ver_line);
                } else {
                    block_wprint_t block_wprint = out_board->block_inner;
                    set_board_block_each(out_board, i, j, BLOCK_NATURE_EMPTY, block_wprint);
                }
            }
        }
    }
}

void cleanup_board(board_t* const out_board)
{
    (void)out_board;
}

void wdraw_board(const board_t* board)
{
    debug();

    my_assert(board != NULL);

    cursor_lock();
    wgotoxy(board->pos_wprint.x, board->pos_wprint.y);
    for (int i = 0; i < board->height; ++i) {
        static wchar_t wbuf[TETRIS_PLAY_BOARD_WIDTH + 1];
        for (int j = 0; j < board->width; ++j) {
            wbuf[j] = board->grid[i][j].wprint;
        }
        wbuf[board->width] = L'\0';
        wdraw_row_newline(wbuf, board->width_wprint);
    }
    cursor_unlock();
}

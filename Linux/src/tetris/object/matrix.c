#include "matrix.h"
#include "debug.h"
#include "draw/draw_tool.h"

#include <assert.h>

static inline void set_matrix_block_each(matrix_t* const out_matrix, int i, int j, block_nature_t nature, block_wprint_t wprint)
{
    set_block_each(out_matrix->grid[i] + j, nature, wprint);
}

void init_matrix(matrix_t* const out_matrix)
{
    set_matrix_block_each(out_matrix, 0, 0, BLOCK_NATURE_FULL, out_matrix->block_corner_top_left);
    set_matrix_block_each(out_matrix, 0, out_matrix->width - 1, BLOCK_NATURE_FULL, out_matrix->block_corner_top_right);
    set_matrix_block_each(out_matrix, out_matrix->height - 1, 0, BLOCK_NATURE_FULL, out_matrix->block_corner_bot_left);
    set_matrix_block_each(out_matrix, out_matrix->height - 1, out_matrix->width - 1, BLOCK_NATURE_FULL, out_matrix->block_corner_bot_right);

    for (int i = 0; i < out_matrix->height; ++i) {
        const int sky_line_i = out_matrix->skyline_pos.x - TETRIS_PLAY_MATRIX_POS_X;
        if (i == 0 || i == out_matrix->height - 1) {
            for (int j = 1; j < out_matrix->width - 1; ++j) {
                set_matrix_block_each(out_matrix, i, j, i == sky_line_i ? BLOCK_NATURE_EMPTY : BLOCK_NATURE_FULL, out_matrix->block_hor_line);
            }
        } else {
            for (int j = 0; j < out_matrix->width; ++j) {
                if (j == 0 || j == out_matrix->width - 1) {
                    set_matrix_block_each(out_matrix, i, j, BLOCK_NATURE_FULL, out_matrix->block_ver_line);
                } else {
                    block_wprint_t block_wprint = i > out_matrix->skyline_i ? out_matrix->block_in_play : BLOCK_WPRINT_EMPTY;
                    set_matrix_block_each(out_matrix, i, j, BLOCK_NATURE_EMPTY, block_wprint);
                }
            }
        }
    }
}

void cleanup_matrix(matrix_t* const out_matrix)
{
    (void)out_matrix;
}

void wdraw_matrix(const matrix_t* matrix)
{
    cursor_lock();
    wgotoxy(matrix->in_play_pos_wprint.x, matrix->in_play_pos_wprint.y);
    // for (int i = 0; i < matrix->height; ++i) {
    //     static wchar_t s_wbuf[TETRIS_PLAY_MATRIX_WIDTH + 1];
    //     for (int j = 0; j < matrix->width; ++j) {
    //         s_wbuf[j] = matrix->grid[i][j].wprint;
    //     }
    //     s_wbuf[matrix->width] = L'\0';
    //     wdraw_row_newline(s_wbuf, matrix->width_wprint);
    // }
    traverse_matrix_in_play_row(i, matrix) {
        static wchar_t s_wbuf[TETRIS_PLAY_MATRIX_WIDTH + 1];
        traverse_matrix_in_play_col(j, matrix) {
            s_wbuf[j - 1] = matrix->grid[i][j].wprint;
            // assert(matrix->grid[i][j].nature == BLOCK_NATURE_EMPTY);
        }
        s_wbuf[matrix->width - 2] = L'\0';
        wdraw_row_newline(s_wbuf, matrix->width_wprint - 2 * 2);
    }
    cursor_unlock();
}

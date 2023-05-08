#ifndef __MATRIX__H
#define __MATRIX__H

#include <pthread.h>
#include <wchar.h>

#include "block.h"
#include "pthread_macro.h"
#include "tetris/object/tetromino.h"
#include "tetris/scene/tetris_play_screen.h"

#define TETRIS_PLAY_MATRIX_INNER_HEIGHT (20)
#define TETRIS_PLAY_MATRIX_INNER_WIDTH (10)

#define TETRIS_PLAY_MATRIX_HEIGHT (TETRIS_PLAY_MATRIX_INNER_HEIGHT + 2)
#define TETRIS_PLAY_MATRIX_WIDTH (TETRIS_PLAY_MATRIX_INNER_WIDTH + 2)
#define TETRIS_PLAY_MATRIX_HEIGHT_WPRINT (TETRIS_PLAY_MATRIX_HEIGHT)
#define TETRIS_PLAY_MATRIX_WIDTH_WPRINT (2 * TETRIS_PLAY_MATRIX_WIDTH)

#define TETRIS_PLAY_MATRIX_POS_X_WPRINT \
    (TETRIS_PLAY_SINGLE_SCREEN_POS_X_WPRINT + 8)
#define TETRIS_PLAY_MATRIX_POS_Y_WPRINT \
    (TETRIS_PLAY_SINGLE_SCREEN_POS_Y_WPRINT + (TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT - TETRIS_PLAY_MATRIX_WIDTH_WPRINT) / 2 + 0)
#define TETRIS_PLAY_MATRIX_POS_X TETRIS_PLAY_MATRIX_POS_X_WPRINT
#define TETRIS_PLAY_MATRIX_POS_Y (TETRIS_PLAY_MATRIX_POS_Y_WPRINT / 2)

#define TETRIS_PLAY_SKYLINE_POS_X (TETRIS_PLAY_MATRIX_POS_X + (TETRIS_PLAY_MATRIX_HEIGHT - 2 - 20))

#define MATRIX_FRAME_HEIGHT (TETRIS_PLAY_MATRIX_HEIGHT + 2)
#define MATRIX_FRAME_WIDTH (TETRIS_PLAY_MATRIX_WIDTH + 2)

#define MATRIX_FRAME_POS_X (TETRIS_PLAY_MATRIX_POS_X - 1)
#define MATRIX_FRAME_POS_Y (TETRIS_PLAY_MATRIX_POS_Y - 1)
#define MATRIX_FRAME_POS_X_WPRINT (TETRIS_PLAY_MATRIX_POS_X_WPRINT - 1)
#define MATRIX_FRAME_POS_Y_WPRINT (TETRIS_PLAY_MATRIX_POS_Y_WPRINT - 2)

#define MATRIX_INNTER_BLOCK_WPRINT BLOCK_WPRINT_WHITE_LARGE_SQUARE
#define MATRIX_WALL_BLOCK_WPRINT BLOCK_WPRINT_NEW_MOON

// typedef block_t row_t[TETRIS_PLAY_MATRIX_WIDTH];
typedef struct {
    const wchar_t block_corner_top_left;
    const wchar_t block_corner_top_right;
    const wchar_t block_corner_bot_left;
    const wchar_t block_corner_bot_right;
    const wchar_t block_ver_line;
    const wchar_t block_hor_line;
    const wchar_t block_inner;
    const wchar_t block_skyline;

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

    // row_t grid[TETRIS_PLAY_MATRIX_HEIGHT];
    block_t grid[TETRIS_PLAY_MATRIX_HEIGHT][TETRIS_PLAY_MATRIX_WIDTH];
} matrix_t;

#define traverse_inner_row(i, matrix) for (int i = matrix->skyline_pos.x - matrix->pos.x + 1; i < matrix->height - 1; ++i)
#define traverse_inner_row_reverse(i, matrix) for (int i = matrix->height - 2; i > matrix->skyline_pos.x - matrix->pos.x; --i)
#define traverse_inner_col(j, matrix) for (int j = 1; j <= matrix->width - 2; ++j)
#define traverse_inner(i, j, matrix) traverse_inner_row(i, matrix) traverse_inner_col(j, matrix)

static inline bool is_all_of_row(const matrix_t* matrix, int i, block_nature_t nature)
{
    bool is_all = true;
    traverse_inner_col(j, matrix) {
        is_all &= (matrix->grid[i][j].nature == nature);
    }
    return is_all;
}

void init_matrix(matrix_t* const out_matrix);
void cleanup_matrix(matrix_t* const out_matrix);
void wdraw_matrix(const matrix_t* matrix);
void wdraw_matrix_range(const matrix_t* matrix, int si, int ei, int sj, int ej);

#endif /* __MATRIX__H */
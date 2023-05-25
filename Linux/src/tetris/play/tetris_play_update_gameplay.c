#include <math.h>
#include <stdio.h>

#include "chronometry.h"
#include "debug.h"
#include "tetris/scene/tetris_play_renderer.h"
#include "tetris_play_tetromino_manager.h"
#include "tetris_play_ghost_piece.h"
#include "tetris_play_update_tetromino_in_play_status.h"
#include "tetris_play_update_gameplay.h"

static inline void lockdown_tetromino(matrix_t* const out_matrix, const tetromino_t* tetro)
{
    tetromino_shape_t shape = get_tetromino_shape(tetro->shape_id, tetro->dir);
    traverse_shape(i, j, shape) {
        int ex = (int)tetro->pos.x + i;
        int ey = (int)tetro->pos.y + j;
        int ei = ex - out_matrix->pos.x;
        int ej = ey - out_matrix->pos.y;
        out_matrix->grid[ei][ej].nature = tetro->block.nature;
        if (ei > out_matrix->skyline_i) {
            out_matrix->grid[ei][ej].wprint = tetro->block.wprint;
        }
    }
}

static int clear_filled_lines(matrix_t* const out_matrix)
{
    static int s_que[4];
    int end = 0;
    /* Check full lines */
    {
        traverse_matrix_in_play_row_reverse(i, out_matrix) {
            if (is_all_of_matrix_row(out_matrix, i, BLOCK_NATURE_FULL)) {
                s_que[end++] = i;
            }
        }
        if (end == 0) {
            return 0;
        }
    }
    /* Reflect them visually */
    {
        traverse_matrix_in_play_col(j, out_matrix) {
            for (int ptr = 0; ptr < end; ++ptr) {
                int i = s_que[ptr];
                set_block_each(&out_matrix->grid[i][j], BLOCK_NATURE_EMPTY, MATRIX_INNTER_BLOCK_WPRINT);
                // pos_int_t pos_wprint = convert_intpos_intwprint(create_posint(out_matrix->pos.x + i, out_matrix->pos.y + j));
                pos_int_t pos_wprint = create_posint(out_matrix->in_play_pos_wprint.x + i - out_matrix->in_play_height - 1, out_matrix->in_play_pos_wprint.y + 2 * (j - 1));
                wdraw_unit_matrix_at_r(out_matrix->grid[i][j].wprint, pos_wprint.x, pos_wprint.y);
            }
            static const float S_CLEAR_MATRIX_INTERVAL_SEC = 0.015f;
            nanosleep_chrono(TO_NSEC(S_CLEAR_MATRIX_INTERVAL_SEC));
            fflush(stdout);
        }
    }
    /* Fill empty lines */
    {
        for (int ptr = 0; ptr < end; ++ptr) {
            int L = s_que[ptr];
            int R;
            if (ptr == end - 1) {
                // R = s_que[ptr] - 1;
                // while (R >= filled_min_x && !is_all_of_matrix_row(out_matrix, R, BLOCK_NATURE_EMPTY)) {
                //     R -= 1;
                // }
                // hmm...
                R = out_matrix->skyline_i;
            } else {
                R = s_que[ptr + 1];
            }
            int move_dist = ptr + 1;
            for (int i = L - 1; i > R; --i) {
                traverse_matrix_in_play_col(j, out_matrix)
                {
                    out_matrix->grid[i + move_dist][j] = out_matrix->grid[i][j];
                    set_block_each(&out_matrix->grid[i][j], BLOCK_NATURE_EMPTY, MATRIX_INNTER_BLOCK_WPRINT);
                }
            }
        }
        wdraw_matrix(out_matrix);
        fflush(stdout);
    }
    return end;
}

static inline bool is_at_skyline(const matrix_t* matrix, const tetromino_t* tetro)
{
    my_assert(is_valid_tetromino(tetro));
    
    tetromino_shape_t shape = get_tetromino_shape(tetro->shape_id, tetro->dir);
    int first_pos_x = TETRIS_PLAY_TETROMINO_IN_PLAY_POS_X_MIN;
    traverse_shape(i, _, shape) {
        first_pos_x = (int)tetro->pos.x + i;
        goto skyline_return_line;
    }

skyline_return_line:
    return first_pos_x <= matrix->skyline_pos.x;
}


void process_tetromino_status(tetromino_in_play_status_t status, tetris_play_manager_t* const out_play_manager)
{
    switch (status) {
    case TETROMINO_IN_PLAY_STATUS_MOVE:
        /* intentional fallthrough */
    case TETROMINO_IN_PLAY_STATUS_ROTATE:
        render_out(out_play_manager);
        break;
    case TETROMINO_IN_PLAY_STATUS_ONTHEGROUND:
        lockdown_tetromino(&out_play_manager->tetro_man.matrix, out_play_manager->tetro_man.tetromino_in_play);
        render_out(out_play_manager);
        int lines = clear_filled_lines(&out_play_manager->tetro_man.matrix);
        inc_cleared_lines(&out_play_manager->tetro_man.stat, lines);
        update_tetromino_manager_after_lockdown(&out_play_manager->tetro_man, lines);
        if (is_at_skyline(&out_play_manager->tetro_man.matrix, out_play_manager->tetro_man.tetromino_in_play)) {
            out_play_manager->status = TETRIS_PLAY_STATUS_GAMEOVER;
        }
        cleanup_lockdown_tetromino_in_play(&out_play_manager->tetro_man);
        break;
    case TETROMINO_IN_PLAY_STATUS_ONTHEWALL:
        /* intentional fallthrough */
    case TETROMINO_IN_PLAY_STATUS_NULL:
        /* intentional fallthrough */
    }
}

void update_gameplay(tetris_play_manager_t* const out_play_manager)
{
    tetromino_in_play_status_t res = update_tetromino_manager(&out_play_manager->tetro_man, out_play_manager->game_delta_time);
    process_tetromino_status(res, out_play_manager);
}


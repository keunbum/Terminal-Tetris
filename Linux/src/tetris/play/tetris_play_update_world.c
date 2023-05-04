#include <math.h>
#include <stdio.h>

#include "chronometry.h"
#include "debug.h"
#include "tetris/scene/tetris_play_renderer.h"
#include "tetris_play_tetromino_manager.h"
#include "tetris_play_tetromino_silhouette.h"
#include "tetris_play_update_tetromino_status.h"
#include "tetris_play_update_world.h"

static inline void petrify_tetromino(board_t* const out_board, const tetromino_t* tetro)
{
    tetromino_symbol_t symbol = get_tetromino_symbol(tetro->symbol_id, tetro->dir);
    traverse_symbol(i, j, symbol) {
        int ex = (int)tetro->pos.x + i;
        int ey = (int)tetro->pos.y + j;
        int ei = ex - out_board->pos.x;
        int ej = ey - out_board->pos.y;
        out_board->grid[ei][ej].nature = tetro->block.nature;
        if (ei > out_board->skyline) {
            out_board->grid[ei][ej].wprint = tetro->block.wprint;
        }
    }
}

static int clear_filled_lines(board_t* const out_board)
{
    static int s_que[4];
    int end = 0;
    /* Check full lines */
    {
        traverse_inner_row_reverse(i, out_board) {
            if (is_all_of_row(out_board, i, BLOCK_NATURE_FULL)) {
                s_que[end++] = i;
            }
        }
        if (end == 0) {
            return 0;
        }
    }
    /* Reflect them visually */
    {
        traverse_inner_col(j, out_board) {
            for (int ptr = 0; ptr < end; ++ptr) {
                int i = s_que[ptr];
                set_block_each(&out_board->grid[i][j], BLOCK_NATURE_EMPTY, BOARD_INNTER_BLOCK_WPRINT);
                pos_int_t pos_wprint = get_intpos_intwprint(create_posint(out_board->pos.x + i, out_board->pos.y + j));
                wdraw_unit_matrix_at_r(out_board->grid[i][j].wprint, pos_wprint.x, pos_wprint.y);
            }
            static const float S_CLEAR_BOARD_INTERVAL_SEC = 0.015f;
            nanosleep_chrono(TO_NSEC(S_CLEAR_BOARD_INTERVAL_SEC));
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
                // while (R >= filled_min_x && !is_all_of_row(out_board, R, BLOCK_NATURE_EMPTY)) {
                //     R -= 1;
                // }
                // hmm...
                R = out_board->skyline;
            } else {
                R = s_que[ptr + 1];
            }
            int move_dist = ptr + 1;
            for (int i = L - 1; i > R; --i) {
                traverse_inner_col(j, out_board)
                {
                    out_board->grid[i + move_dist][j] = out_board->grid[i][j];
                    set_block_each(&out_board->grid[i][j], BLOCK_NATURE_EMPTY, BOARD_INNTER_BLOCK_WPRINT);
                }
            }
        }
        wdraw_board(out_board);
        fflush(stdout);
    }
    return end;
}

static inline bool is_at_skyline(const board_t* board, const tetromino_t* tetro)
{
    my_assert(is_valid_tetromino(tetro));
    
    tetromino_symbol_t symbol = get_tetromino_symbol(tetro->symbol_id, tetro->dir);
    int first_pos_x = TETRIS_PLAY_TETROMINO_POS_X_MIN;
    
    traverse_symbol(i, _, symbol) {
        first_pos_x = (int)tetro->pos.x + i;
        goto skyline_return_line;
    }

skyline_return_line:
    return first_pos_x <= board->skyline_pos.x;
}


void process_tetromino_status(tetromino_status_t status, tetris_play_manager_t* const out_play_manager)
{
    switch (status) {
    case TETROMINO_STATUS_MOVE:
        /* intentional fallthrough */
    case TETROMINO_STATUS_ROTATE:
        render_out(out_play_manager);
        break;
    case TETROMINO_STATUS_ONTHEGROUND:
        petrify_tetromino(&out_play_manager->tetro_man.board, out_play_manager->tetro_man.tetro_main);
        render_out(out_play_manager);
        int lines = clear_filled_lines(&out_play_manager->tetro_man.board);
        inc_cleared_lines(&out_play_manager->tetro_man.stat, lines);
        update_tetromino_manager_info(&out_play_manager->tetro_man, lines);
        if (is_at_skyline(&out_play_manager->tetro_man.board, out_play_manager->tetro_man.tetro_main)) {
            out_play_manager->status = TETRIS_PLAY_STATUS_GAMEOVER;
        }
        cleanup_tetromino_ontheground(&out_play_manager->tetro_man);
        break;
    case TETROMINO_STATUS_ONTHEWALL:
        /* intentional fallthrough */
    case TETROMINO_STATUS_NULL:
        /* intentional fallthrough */
    }
}

void update_gameworld(tetris_play_manager_t* const out_play_manager)
{
    tetromino_status_t res = update_tetromino_manager(&out_play_manager->tetro_man, out_play_manager->game_delta_time);
    process_tetromino_status(res, out_play_manager);
}


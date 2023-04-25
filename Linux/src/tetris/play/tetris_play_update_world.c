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
    debug();

    tetromino_symbol_t symbol = get_tetromino_symbol(tetro->symbol_id, tetro->dir);

    traverse_symbol(i, j, symbol)
    {
        int ex = (int)tetro->pos.x + i;
        int ey = (int)tetro->pos.y + j;
        my_assert(TETRIS_PLAY_TETROMINO_POS_X_MIN <= ex && ex <= TETRIS_PLAY_TETROMINO_POS_X_MAX);
        my_assert(TETRIS_PLAY_TETROMINO_POS_Y_MIN <= ey && ey <= TETRIS_PLAY_TETROMINO_POS_Y_MAX);
        int ei = ex - out_board->pos.x;
        int ej = ey - out_board->pos.y;
        my_assert(1 <= ei && ei <= out_board->height - 2);
        my_assert(1 <= ej && ej <= out_board->width - 2);
        out_board->grid[ei][ej].nature = tetro->block.nature;
        if (ei > out_board->skyline) {
            out_board->grid[ei][ej].wprint = tetro->block.wprint;
        }
    }
}

static void clear_filled_lines(board_t* const out_board)
{
    debug();

    static const double S_CLEAR_BOARD_INTERVAL_SEC = 0.05;
    static int s_que[4];
    int end = 0;
    /* Check full lines */
    traverse_inner_row_reverse(i, out_board)
    {
        if (is_all_of_row(out_board, i, BLOCK_NATURE_FULL)) {
            s_que[end++] = i;
            my_assert(end <= 4);
            assert(end <= 4);
        }
    }
    if (end == 0) {
        return;
    }
    /* Reflect them visually */
    traverse_inner_col(j, out_board)
    {
        for (int ptr = 0; ptr < end; ++ptr) {
            int i = s_que[ptr];
            set_block_each(&out_board->grid[i][j], BLOCK_NATURE_EMPTY, BLOCK_WPRINT_WHITE_LARGE_SQUARE);
            pos_int_t pos_wprint = get_intpos_intwprint(create_posint(out_board->pos.x + i, out_board->pos.y + j));
            wdraw_unit_matrix_at_r(out_board->grid[i][j].wprint, pos_wprint.x, pos_wprint.y);
        }
        ewprintf("\n");
        fflush(stdout);
        nanosleep_chrono(TO_NSEC(S_CLEAR_BOARD_INTERVAL_SEC));
    }
    /* Fill empty lines */
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
                ewprintf("(%d, %d) --> (%d, %d)\n", i, j, i + move_dist, j);
                out_board->grid[i + move_dist][j] = out_board->grid[i][j];
                set_block_each(&out_board->grid[i][j], BLOCK_NATURE_EMPTY, BLOCK_WPRINT_WHITE_LARGE_SQUARE);
            }
            ewprintf("\n");
        }
    }
    wdraw_board(out_board);
    fflush(stdout);
}

static inline bool is_at_skyline(const board_t* board, const tetromino_t* tetro)
{
    debug();

    my_assert(tetro != NULL);

    tetromino_symbol_t symbol = get_tetromino_symbol(tetro->symbol_id, tetro->dir);

    int first_pos_x = TETRIS_PLAY_TETROMINO_POS_X_MIN;

    traverse_symbol(i, _, symbol)
    {
        first_pos_x = (int)tetro->pos.x + i;
        goto skyline_return_line;
    }
skyline_return_line:
    return first_pos_x <= board->skyline_pos.x;
}

void process_tetromino_try_status(tetromino_status_t status, tetris_play_manager_t* const out_play_manager)
{
    // debug();

    switch (status) {
    case TETROMINO_STATUS_ONTHEGROUND:
        petrify_tetromino(&out_play_manager->tetro_man.board, out_play_manager->tetro_man.tetro_main);
        render_out(out_play_manager);
        clear_filled_lines(&out_play_manager->tetro_man.board);
        if (is_at_skyline(&out_play_manager->tetro_man.board, out_play_manager->tetro_man.tetro_main)) {
            out_play_manager->status = TETRIS_PLAY_STATUS_GAMEOVER;
        }
        cleanup_tetromino_free(out_play_manager->tetro_man.tetro_main);
        out_play_manager->tetro_man.is_swaped_once = false;
        out_play_manager->tetro_man.tetromino_init_velocity += out_play_manager->tetro_man.unit_velocity;
        out_play_manager->tetro_man.tetro_main = NULL;
        break;
    case TETROMINO_STATUS_MOVE:
        /* intentional fallthrough */
    case TETROMINO_STATUS_ROTATE:
            render_out(out_play_manager);
        break;
    case TETROMINO_STATUS_ONTHEWALL:
        /* Do Nothing */
        break;
    case TETROMINO_STATUS_NULL:
        /* Do Nothing */
        break;
#ifdef TETRIS_DEBUG
    default:
        my_assert(false);
#endif
    }
}

void update_gameworld(tetris_play_manager_t* const out_play_manager)
{
    debug();

    /* As long as you run the input processing thread separately,
       you need to take care of the critical section problem. */
    lock_tetromino_manager(&out_play_manager->tetro_man);
    tetromino_status_t ret = update_tetromino_manager(&out_play_manager->tetro_man, out_play_manager->game_delta_time);
    process_tetromino_try_status(ret, out_play_manager);
    unlock_tetromino_manager(&out_play_manager->tetro_man);
}

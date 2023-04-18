#include <stdio.h>
#include <math.h>

#include "debug.h"
#include "tetris/scene/tetris_play_renderer.h"
#include "tetris_play_tetromino_manager.h"
#include "tetris_play_update_tetromino_status.h"
#include "tetris_play_update_world.h"
#include "chronometry.h"

static inline void petrify_tetromino(board_t* const out_board, const tetromino_t* tetro)
{
    debug();

    tetromino_matrix_t matrix = get_tetromino_matrix(tetro->symbol_id, tetro->dir);
    tetromino_matrix_n_t n = get_tetromino_matrix_n(tetro->symbol_id);

    for (int idx = 0; idx < n * n; ++idx) {
        if (is_empty_block(matrix, idx)) {
            continue;
        }
        int i = idx / n;
        int j = idx % n;
        pos_t each_pos = { tetro->pos.x + i, tetro->pos.y + j };
        int ex = (int)each_pos.x;
        int ey = (int)each_pos.y;
        my_assert(TETRIS_PLAY_TETROMINO_POS_X_MIN <= ex && ex <= TETRIS_PLAY_TETROMINO_POS_X_MAX);
        my_assert(TETRIS_PLAY_TETROMINO_POS_Y_MIN <= ey && ey <= TETRIS_PLAY_TETROMINO_POS_Y_MAX);
        int ei = ex - (int)out_board->pos.x;
        int ej = ey - (int)out_board->pos.y;
        my_assert(1 <= ei && ei <= out_board->height - 2);
        my_assert(1 <= ej && ej <= out_board->width - 2);
        out_board->grid[ei][ej].nature = tetro->block.nature;
        if (ei > out_board->skyline) {
            out_board->grid[ei][ej].wprint = tetro->block.wprint;
        }
    }
}

static inline bool is_row_all(const board_t* board, int i, block_nature_t nature)
{
    bool is_all = true;
    traverse_inner_col(j, board) {
        is_all &= board->grid[i][j].nature == nature;
    }
    return is_all;
}

static void clear_board_filled_lines(board_t* const out_board)
{
    static const float S_CLEAR_BOARD_INTERVAL_SEC = 0.05f;
    static int s_stk[TETRIS_PLAY_BOARD_INNER_HEIGHT];
    int top = 0;
    /* Check full lines */
    traverse_inner_row(i, out_board) {
        if (is_row_all(out_board, i, BLOCK_NATURE_FULL)) {
            s_stk[top++] = i;
        }
    }
    if (top == 0) {
        return;
    }
    /* Reflect them visually */
    traverse_inner_col(j, out_board) {
        for (int ptr = 0; ptr < top; ++ptr) {
            int i = s_stk[ptr];
            set_block_each(&out_board->grid[i][j], BLOCK_NATURE_EMPTY, BLOCK_WPRINT_WHITE_LARGE_SQUARE);
            pos_int_t pos_wprint = get_intpos_to_intwprint(create_pos_int(out_board->pos.x + i, out_board->pos.y + j));
            wdraw_unit_matrix_at_r(out_board->grid[i][j].wprint, pos_wprint.x, pos_wprint.y);
            fflush(stdout);
        }
        nanosleep_chrono(TO_NSEC(S_CLEAR_BOARD_INTERVAL_SEC));
    }
    /* Fill board empty lines */
    const int min_x = out_board->skyline - 3;
    int L = s_stk[0];
    int R = L + 1;
    while (L < out_board->skyline) {
        while (R <= min_x && is_row_all(out_board, L, BLOCK_NATURE_EMPTY)) {
            R += 1;
        }
        if (R == min_x - 1) {
            break;
        }
        /* Implement from here. */
        L += 1;
    }
}

static inline bool is_at_skyline(const board_t* board, const tetromino_t* tetro)
{
    debug();

    my_assert(tetro != NULL);

    tetromino_matrix_t matrix = get_tetromino_matrix(tetro->symbol_id, tetro->dir);
    tetromino_matrix_n_t n = get_tetromino_matrix_n(tetro->symbol_id);
    int last_pos_x = TETRIS_PLAY_TETROMINO_POS_X_MIN - 1;
    for (int idx = 0; idx < n * n; ++idx) {
        if (is_empty_block(matrix, idx)) {
            continue;
        }
        int i = idx / n;
        last_pos_x = (int)tetro->pos.x + i;
    }
    my_assert(TETRIS_PLAY_TETROMINO_POS_X_MIN <= last_pos_x);
    return last_pos_x <= board->skyline_pos.x;
}

void process_tetromino_try_status(tetromino_try_status_t status, tetris_play_manager_t* const out_play_manager)
{
    /* As long as you run the input processing thread separately, you need to take care of the critical section problem. */
    switch (status) {
    case TETROMINO_TRY_STATUS_ONTHEGROUND:
        petrify_tetromino(&out_play_manager->board, out_play_manager->tetro_man.tetro_main);
        render_out(out_play_manager);
        clear_board_filled_lines(&out_play_manager->board);
        if (is_at_skyline(&out_play_manager->board, out_play_manager->tetro_man.tetro_main)) {
            out_play_manager->status = TETRIS_PLAY_STATUS_GAMEOVER;
        }
        cleanup_tetromino_free(out_play_manager->tetro_man.tetro_main);
        out_play_manager->tetro_man.tetro_main = NULL;
        break;
    case TETROMINO_TRY_STATUS_MOVE:
        /* intentional fallthrough */
    case TETROMINO_TRY_STATUS_ROTATE:
        render_out(out_play_manager);
        break;
    case TETROMINO_TRY_STATUS_INPLACE:
        /* Do Nothing */
        break;
    case TETROMINO_TRY_STATUS_NULL:
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

    lock_board(&out_play_manager->board);
    tetromino_try_status_t ret = update_tetromino_manager(&out_play_manager->tetro_man, &out_play_manager->board, out_play_manager->game_delta_time);
    process_tetromino_try_status(ret, out_play_manager);
    unlock_board(&out_play_manager->board);
}

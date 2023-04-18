#include <stdio.h>

#include "debug.h"
#include "tetris/scene/tetris_play_renderer.h"
#include "tetris_play_tetromino_manager.h"
#include "tetris_play_update_tetromino_status.h"
#include "tetris_play_update_world.h"

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
        if (ex < 0) {
            continue;
        }
        my_assert(TETRIS_PLAY_TETROMINO_POS_X_MIN <= ex && ex <= TETRIS_PLAY_TETROMINO_POS_X_MAX);
        my_assert(TETRIS_PLAY_TETROMINO_POS_Y_MIN <= ey && ey <= TETRIS_PLAY_TETROMINO_POS_Y_MAX);
        int ei = ex - (int)out_board->pos.x;
        int ej = ey - (int)out_board->pos.y;
        my_assert(1 <= ei && ei <= out_board->height - 2);
        my_assert(1 <= ej && ej <= out_board->width - 2);
        // Hmm.. need to draw too?
        set_block(&out_board->grid[ei][ej], tetro->block);
    }
}

static inline bool is_at_skyline(const tetromino_t* tetro)
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
    return last_pos_x <= TETRIS_PLAY_SKY_LINE_POS_X;
}

void process_tetromino_try_status(tetromino_try_status_t status, tetris_play_manager_t* const out_play_manager)
{
    /* As long as you run the input processing thread separately, you need to take care of the critical section problem. */
    switch (status) {
    case TETROMINO_TRY_STATUS_ONTHEGROUND:
        petrify_tetromino(&out_play_manager->board, out_play_manager->tetro_man.tetro_main);
        // clear_filled_lines(); --> maybe internally.
        // reflect_them_visually();
        render_out(out_play_manager);
        if (is_at_skyline(out_play_manager->tetro_man.tetro_main)) {
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
#ifdef TETRIS_DEBUG
    case TETROMINO_TRY_STATUS_INPLACE:
        /* intentional fallthrough */
    case TETROMINO_TRY_STATUS_NULL:
        /* Do Nothing */
        break;
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

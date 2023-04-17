#include <stdio.h>

#include "debug.h"
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
        int ni = i + ex - ((int)out_board->pos.x + 1);
        int nj = j + ey - ((int)out_board->pos.y + 1);
        set_block(out_board->grid[ni] + nj, tetro->block);
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

// static tetromino_try_status_t update_main_tetromino_r(tetris_play_manager_t* const out_play_manager, tetromino_t* const restrict out_tetromino, game_time_t game_delta_time)
// {
//     debug();

//     tetris_play_tetromino_manager_lock();
//     if (out_tetromino->id == -1) {
// pos_t init_pos = { TETRIS_PLAY_TETROMINO_INIT_POS_X, TETRIS_PLAY_TETROMINO_INIT_POS_Y };
//         spawn_tetromino(&out_play_manager->tetro_man.tetro_gen, out_tetromino, init_pos, TETRIS_PLAY_TETROMINO_INIT_VELOCITY);
//         inc_tetromino_cnt(&out_play_manager->stat, out_tetromino->symbol_id);
//         // update_tetromino_ground_pos(out_board, out_tetromino);
//     }
//     tetris_play_tetromino_manager_unlock();
//     tetromino_try_status_t res = try_move_tetromino_deltatime_r(&out_play_manager->board, out_tetromino, DIR_BOT, game_delta_time);
//     return res;
// }

// static tetromino_try_status_t new_update_main_tetromino_r(tetris_play_manager_t* const out_play_manager, game_time_t game_delta_time)
// {
//     debug();

//     tetromino_manager_t* const tetro_man = &out_play_manager->tetro_man;
//     // ewprintf("tetro_man->tetro_main's pos: (%d, %d)\n", (int)tetro_man->tetro_main.pos.x, (int)tetro_man->tetro_main.pos.y);
//     if (!is_valid_tetromino(tetro_man->tetro_main)) {
//         pos_t tetro_main_init_pos = { TETRIS_PLAY_TETROMINO_INIT_POS_X, TETRIS_PLAY_TETROMINO_INIT_POS_Y };
//         spawn_tetromino_manager_tetro_main(tetro_man, tetro_main_init_pos, TETRIS_PLAY_TETROMINO_INIT_VELOCITY);
//         // ewprintf("after init, tetro_man->tetro_main's pos: (%d, %d)\n", (int)tetro_man->tetro_main.pos.x, (int)tetro_man->tetro_main.pos.y);
//         inc_tetromino_cnt(&out_play_manager->tetro_man.stat, tetro_man->tetro_main->symbol_id);
//     }
//     tetromino_try_status_t res = try_move_tetromino_deltatime_r(&out_play_manager->board, tetro_man->tetro_main, DIR_BOT, game_delta_time);
//     // ewprintf("after move, tetro_main's pos: (%d, %d), \n", (int)tetro_man->tetro_main.pos.x, (int)tetro_man->tetro_main.pos.y);
//     return res;
// }

// void update_gameworld(tetris_play_manager_t* const out_play_manager)
// {
//     debug();

//     tetromino_try_status_t res = update_main_tetromino_r(out_play_manager, &out_play_manager->tetromino, out_play_manager->game_delta_time);
//     /* Maybe race condition?? */
//     if (res == TETROMINO_TRY_STATUS_ONTHEGROUND) {
//         process_tetromino_ontheground_r(out_play_manager);
//     }
// }

tetromino_try_status_t new_update_gameworld(tetris_play_manager_t* const out_play_manager)
{
    debug();

    // tetromino_try_status_t res = new_update_main_tetromino_r(out_play_manager, out_play_manager->game_delta_time);
    tetromino_try_status_t ret = update_tetromino_manager(&out_play_manager->tetro_man, &out_play_manager->board, out_play_manager->game_delta_time);
    /* Maybe race condition?? */
    if (ret == TETROMINO_TRY_STATUS_ONTHEGROUND) {
        petrify_tetromino(&out_play_manager->board, out_play_manager->tetro_man.tetro_main);
        // clear_filled_lines(); --> maybe internally.
        // reflect_them_visually();
        if (is_at_skyline(out_play_manager->tetro_man.tetro_main)) {
            out_play_manager->status = TETRIS_PLAY_STATUS_GAMEOVER;
        }
    }
    return ret;
}

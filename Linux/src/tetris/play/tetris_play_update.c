#include <stdio.h>

#include "debug.h"
#include "tetris_play_update.h"
#include "tetromino_generator.h"
#include "update_tetromino_status.h"

static inline void petrity_tetromino(tetris_play_board_t* const out_board, const tetromino_t* tetro)
{
    debug();

    my_assert(tetro->id != -1);
    polyomino_matrix_t matrix = get_tetromino_matrix(tetro->symbol_id, tetro->rotate_dir);
    polyomino_matrix_n_t n = get_tetromino_matrix_n(tetro->symbol_id);
    for (int idx = 0; idx < n * n; ++idx) {
        if (is_empty_block(matrix, idx)) {
            continue;
        }
        int i = idx / n;
        int j = idx % n;
        pos_t each_pos = { tetro->pos.x + i, tetro->pos.y + j };
        if (each_pos.x < 0) {
            continue;
        }
        my_assert(each_pos.x >= 0);
        my_assert(each_pos.x < TETRIS_PLAY_BOARD_HEIGHT);
        my_assert(0 <= each_pos.y && each_pos.y < TETRIS_PLAY_BOARD_WIDTH);
        tetris_play_board_lock();
        out_board->grid[(int)each_pos.x][(int)each_pos.y] = tetro->id;
        tetris_play_board_unlock();
    }
}

static inline bool is_at_skyline(const tetromino_t* tetro)
{
    debug();

    my_assert(tetro->id != -1);
    my_assert(0 <= tetro->symbol_id && tetro->symbol_id < TOTAL_TETROMINO_NUM_OF_KINDS);
    polyomino_matrix_t matrix = get_tetromino_matrix(tetro->symbol_id, tetro->rotate_dir);
    polyomino_matrix_n_t n = get_tetromino_matrix_n(tetro->symbol_id);
    tetris_play_tetromino_unlock();
    pos_e_t last_pos_x = TETRIS_PLAY_TETROMINO_POS_X_MIN - 1;
    for (int idx = 0; idx < n * n; ++idx) {
        if (is_empty_block(matrix, idx)) {
            continue;
        }
        int i = idx / n;
        last_pos_x = tetro->pos.x + i;
    }
    my_assert(last_pos_x >= TETRIS_PLAY_TETROMINO_POS_X_MIN);
    return last_pos_x < 0;
}

static tetromino_status_t update_tetromino_r(tetris_play_board_t* const restrict out_board, tetromino_t* const restrict out_tetromino, game_time_t game_delta_time)
{
    debug();

    tetris_play_tetromino_lock();
    if (out_tetromino->id == -1) {
        pos_t init_pos = { TETRIS_PLAY_TETROMINO_INIT_POS_X, TETRIS_PLAY_TETROMINO_INIT_POS_Y };
        spawn_tetromino(out_tetromino, init_pos, NEW_TETRIS_PLAY_TETROMINO_INIT_VELOCITY);
        update_tetromino_ground_pos(out_board, out_tetromino);
    }
    tetris_play_tetromino_unlock();
    tetromino_status_t res = new_try_move_tetromino_r(out_board, out_tetromino, DIR_BOT, game_delta_time);
    return res;
}

static void process_tetromino_ontheground(tetris_play_manager_t* const out_play_manager)
{
    out_play_manager->tetromino.id = -1;
    out_play_manager->prev_tetromino.id = -1;
    petrity_tetromino(&out_play_manager->board, &out_play_manager->tetromino);
    // clear_filled_lines(); --> maybe internally.
    // reflect_them_visually();
    if (is_at_skyline(&out_play_manager->tetromino)) {
        out_play_manager->status = TETRIS_PLAY_STATUS_GAMEOVER;
    }
}

static void process_tetromino_ontheground_r(tetris_play_manager_t* const out_play_manager)
{
    tetris_play_tetromino_lock();
    process_tetromino_ontheground(out_play_manager);
    tetris_play_tetromino_unlock();
}

void update_gameworld(tetris_play_manager_t* const out_play_manager)
{
    debug();

    tetromino_status_t res = update_tetromino_r(&out_play_manager->board, &out_play_manager->tetromino, out_play_manager->game_delta_time);
    /* Maybe race condition?? */
    if (res == TETROMINO_STATUS_ONTHEGROUND) {
        process_tetromino_ontheground_r(out_play_manager);
    }
}
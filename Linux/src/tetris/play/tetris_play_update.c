#include <stdio.h>

#include "debug.h"
#include "tetris_play_update.h"
#include "tetromino_generator.h"

update_lock_t g_update_lock;

static inline void petrity_tetromino(tetris_play_board_t* const out_board, const tetromino_t* tetro)
{
    debug();

    polyomino_matrix_t matrix = get_tetromino_matrix(tetro->symbol_id, tetro->rotate_dir);
    polyomino_matrix_n_t n = get_tetromino_matrix_n(tetro->symbol_id);
    for (int pos = 0; pos < n * n; ++pos) {
        if (is_empty_block(matrix, pos)) {
            continue;
        }
        int i = pos / n;
        int j = pos % n;
        pos_t each_pos = { tetro->pos.x + i, tetro->pos.y + j };
        if (each_pos.x < 0) {
            continue;
        }
        my_assert(each_pos.x >= 0);
        my_assert(each_pos.x < TETRIS_PLAY_BOARD_HEIGHT);
        my_assert(0 <= each_pos.y && each_pos.y < TETRIS_PLAY_BOARD_WIDTH);
        out_board->grid[(int)each_pos.x][(int)each_pos.y] = tetro->id;
    }
}

static inline bool is_at_skyline(const tetromino_t* tetro)
{
    debug();

    my_assert(0 <= tetro->symbol_id && tetro->symbol_id < TOTAL_TETROMINO_NUM_OF_KINDS);
    polyomino_matrix_t matrix = get_tetromino_matrix(tetro->symbol_id, tetro->rotate_dir);
    polyomino_matrix_n_t n = get_tetromino_matrix_n(tetro->symbol_id);
    pos_e_t last_pos_x = TETRIS_PLAY_TETROMINO_POS_X_MIN - 1;
    for (int pos = 0; pos < n * n; ++pos) {
        if (is_empty_block(matrix, pos)) {
            continue;
        }
        int i = pos / n;
        last_pos_x = tetro->pos.x + i;
    }
    my_assert(last_pos_x >= TETRIS_PLAY_TETROMINO_POS_X_MIN);
    return last_pos_x < 0;
}

tetromino_status_t try_move_tetromino_byone_r(const tetris_play_board_t* board, tetromino_t* const out_tetro, dir_t dir)
{
    tetris_play_update_lock();
    tetromino_status_t res = try_move_tetromino_byone(board, out_tetro, dir);
    tetris_play_update_unlock();
    return res;
}

tetromino_status_t try_rotate_tetromino_r(const tetris_play_board_t* board, tetromino_t* const out_tetro, int by)
{
    tetris_play_update_lock();
    tetromino_status_t res = try_rotate_tetromino(board, out_tetro, by);
    tetris_play_update_unlock();
    return res;

}

void petrity_tetromino_r(tetris_play_board_t* const out_board, const tetromino_t* tetro)
{
    tetris_play_update_lock();
    petrity_tetromino(out_board, tetro);
    tetris_play_update_unlock();
}

bool is_at_skyline_r(const tetromino_t* tetro)
{
    tetris_play_update_lock();
    bool res = is_at_skyline(tetro);
    tetris_play_update_unlock();
    return res;
}

static tetromino_status_t update_tetromino_r(tetris_play_board_t* const restrict out_board, tetromino_t* const restrict out_tetromino, game_time_t game_delta_time)
{
    debug();

    tetris_play_update_lock();
    if (out_tetromino->id == -1) {
        pos_t init_pos = { TETRIS_PLAY_TETROMINO_INIT_POS_X, TETRIS_PLAY_TETROMINO_INIT_POS_Y };
        spawn_tetromino(out_tetromino, init_pos, NEW_TETRIS_PLAY_TETROMINO_INIT_VELOCITY);
        new_update_tetromino_ground_pos(out_board, out_tetromino);
    }
    tetromino_status_t res = new_try_move_tetromino(out_board, out_tetromino, DIR_BOT, game_delta_time);
    tetris_play_update_unlock();
    return res;
}

void process_tetromino_ontheground(tetris_play_manager_t* const out_play_manager)
{
    out_play_manager->tetromino.id = -1;
    out_play_manager->prev_tetromino.id = -1;
    petrity_tetromino_r(&out_play_manager->board, &out_play_manager->tetromino);
    // clear_filled_lines(); --> maybe internally.
    // reflect_them_visually();
    if (is_at_skyline_r(&out_play_manager->tetromino)) {
        out_play_manager->status = TETRIS_PLAY_STATUS_GAMEOVER;
    }
}

void update_gameworld(tetris_play_manager_t* const out_play_manager)
{
    debug();

    tetromino_status_t res = update_tetromino_r(&out_play_manager->board, &out_play_manager->tetromino, out_play_manager->game_delta_time);
    /* Maybe race condition?? */
    if (res == TETROMINO_STATUS_ONTHEGROUND) {
        process_tetromino_ontheground(out_play_manager);
    }
}

void harddrop_tetromino_r(tetris_play_manager_t* const out_play_manager)
{
    tetris_play_update_lock();
    harddrop_tetromino(&out_play_manager->tetromino);
    tetris_play_update_unlock();
    tetromino_status_t res = update_tetromino_r(&out_play_manager->board, &out_play_manager->tetromino, out_play_manager->game_delta_time);
    /* Maybe race condition?? */
    if (res == TETROMINO_STATUS_ONTHEGROUND) {
        process_tetromino_ontheground(out_play_manager);
    }    
}
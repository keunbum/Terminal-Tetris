#include "tetris_play_update_tetromino_status.h"

// /* return tetromino's status when moving left, right, or down.
//    implement the rotation operation separately. */
tetromino_try_status_t try_tetromino_next_status(board_t* const restrict out_board, const tetromino_t* restrict tetro, pos_t npos, dir_t ndir)
{
    // debug();

    tetromino_matrix_t matrix = get_tetromino_matrix(tetro->symbol_id, ndir);
    tetromino_matrix_n_t n = get_tetromino_matrix_n(tetro->symbol_id);
    for (int pos = 0; pos < n * n; ++pos) {
        if (is_empty_block(matrix, pos)) {
            continue;
        }
        int i = pos / n;
        int j = pos % n;
        pos_t each_npos = { npos.x + i, npos.y + j };
        my_assert(each_npos.x >= TETRIS_PLAY_TETROMINO_POS_X_MIN);
        if (each_npos.y < 0 || each_npos.y >= out_board->width) {
            ewprintf("hi1\n");
            return TETROMINO_TRY_STATUS_INPLACE;
        }
        if (each_npos.x >= out_board->height) {
            ewprintf("hi2\n");
            return TETROMINO_TRY_STATUS_ONTHEGROUND;
        }
        if (each_npos.x < 0) {
            continue;
        }
        my_assert((int)each_npos.x >= 0);
        my_assert((int)each_npos.x < out_board->height);
        my_assert(0 <= (int)each_npos.y && (int)each_npos.y < out_board->width);
        const block_t* each_block = get_board_grid_block(out_board, i, j);
        const block_nature_t each_nature = get_block_nature(each_block);
        if (each_nature != BLOCK_NATURE_EMPTY) {
            ewprintf("hi3\n");
            return TETROMINO_TRY_STATUS_ONTHEGROUND;
        }
    }
    ewprintf("hi4\n");
    return TETROMINO_TRY_STATUS_MOVED;
}

tetromino_try_status_t try_move_tetromino_deltatime_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, dir_t dir, game_time_t game_delta_time)
{
    debug();

    tetris_play_tetromino_lock();
    if (out_tetro->id == -1) {
        tetris_play_tetromino_unlock();
        return TETROMINO_TRY_STATUS_NULL;
    }
    // hmm...
    static const pos_t S_DIR_VEC[] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
    pos_t npos = {
        out_tetro->pos.x + S_DIR_VEC[dir].x * (pos_e_t)(out_tetro->velocity * game_delta_time),
        out_tetro->pos.y + S_DIR_VEC[dir].y * (pos_e_t)(out_tetro->velocity * game_delta_time)
    };
    tetromino_try_status_t res = try_tetromino_next_status(out_board, out_tetro, npos, out_tetro->dir);
    if (res == TETROMINO_TRY_STATUS_MOVED) {
        out_tetro->pos = npos;
    }
    tetris_play_tetromino_unlock();
    return res;
}

tetromino_try_status_t try_move_tetromino_byone_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, dir_t dir)
{
    debug();

    tetris_play_tetromino_lock();
    if (out_tetro->id == -1) {
        tetris_play_tetromino_unlock();
        return TETROMINO_TRY_STATUS_NULL;
    }
    static const pos_t S_DIR_VEC[] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
    pos_t npos = {
        out_tetro->pos.x + S_DIR_VEC[dir].x * 1,
        out_tetro->pos.y + S_DIR_VEC[dir].y * 1
    };
    tetromino_try_status_t res = try_tetromino_next_status(out_board, out_tetro, npos, out_tetro->dir);
    if (res == TETROMINO_TRY_STATUS_MOVED) {
        out_tetro->pos = npos;
    }
    tetris_play_tetromino_unlock();
    return res;
}

tetromino_try_status_t try_rotate_tetromino_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, int by)
{
    debug();

    tetris_play_tetromino_lock();
    if (out_tetro->id == -1) {
        tetris_play_tetromino_unlock();
        return TETROMINO_TRY_STATUS_NULL;
    }
    dir_t ndir = (out_tetro->dir + by + TOTAL_DIR_NUM_OF_KINDS) % TOTAL_DIR_NUM_OF_KINDS;
    tetromino_try_status_t res = try_tetromino_next_status(out_board, out_tetro, out_tetro->pos, ndir);
    if (res == TETROMINO_TRY_STATUS_MOVED) {
        out_tetro->dir = ndir;
    }
    tetris_play_tetromino_unlock();
    return res;
}

tetromino_try_status_t harddrop_tetromino_r(tetromino_t* const out_tetro)
{
    debug();

    tetris_play_tetromino_lock();
    (void)out_tetro;
    tetris_play_tetromino_unlock();
    return TETROMINO_TRY_STATUS_MOVED;
}

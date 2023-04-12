#include "update_tetromino_status.h"

// /* return tetromino's status when moving left, right, or down.
//    implement the rotation operation separately. */
tetromino_status_t check_tetromino_next_status(const tetris_play_board_t* board, const tetromino_t* tetro, pos_t npos, dir_t ndir)
{
    debug();

    polyomino_matrix_t matrix = get_tetromino_matrix(tetro->symbol_id, ndir);
    polyomino_matrix_n_t n = get_tetromino_matrix_n(tetro->symbol_id);
    for (int pos = 0; pos < n * n; ++pos) {
        if (is_empty_block(matrix, pos)) {
            continue;
        }
        int i = pos / n;
        int j = pos % n;
        pos_t each_npos = { npos.x + i, npos.y + j };
        my_assert(each_npos.x >= TETRIS_PLAY_TETROMINO_POS_X_MIN);
        if (each_npos.y < 0 || each_npos.y >= board->width) {
            ewprintf("hi1\n");
            return TETROMINO_STATUS_INPLACE;
        }
        if (each_npos.x >= board->height) {
            ewprintf("hi2\n");
            return TETROMINO_STATUS_ONTHEGROUND;
        }
        if (each_npos.x < 0) {
            continue;
        }
        my_assert(each_npos.x >= 0);
        my_assert(each_npos.x < board->height);
        my_assert(0 <= each_npos.y && each_npos.y < board->width);
        tetris_play_board_lock();
        tetris_play_board_grid_element_t each_value = board->grid[(int)each_npos.x][(int)each_npos.y];
        tetris_play_board_unlock();
        if (each_value != TETRIS_PLAY_BOARD_GRID_ELEMENT_DEFAULT && each_value != tetro->id) {
            ewprintf("hi3\n");
            return TETROMINO_STATUS_ONTHEGROUND;
        }
    }
    ewprintf("hi4\n");
    return TETROMINO_STATUS_MOVED;
}

tetromino_status_t new_try_move_tetromino_r(const tetris_play_board_t* board, tetromino_t* const out_tetro, dir_t dir, game_time_t game_delta_time)
{
    debug();

    tetris_play_tetromino_lock();
    if (out_tetro->id == -1) {
        tetris_play_tetromino_unlock();
        return TETROMINO_STATUS_NULL;
    }
    // hmm...
    static const pos_t S_DIR_VEC[] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
    pos_t npos = {
        out_tetro->pos.x + S_DIR_VEC[dir].x * (pos_e_t)(out_tetro->velocity * game_delta_time),
        out_tetro->pos.y + S_DIR_VEC[dir].y * (pos_e_t)(out_tetro->velocity * game_delta_time)
    };
    tetromino_status_t res = check_tetromino_next_status(board, out_tetro, npos, out_tetro->rotate_dir);
    if (res == TETROMINO_STATUS_MOVED) {
        out_tetro->pos = npos;
        update_tetromino_ground_pos(board, out_tetro);
    }
    tetris_play_tetromino_unlock();
    return res;
}

tetromino_status_t try_move_tetromino_byone_r(const tetris_play_board_t* board, tetromino_t* const out_tetro, dir_t dir)
{
    debug();
    tetris_play_tetromino_lock();
    if (out_tetro->id == -1) {
        tetris_play_tetromino_unlock();
        return TETROMINO_STATUS_NULL;
    }
    static const pos_t S_DIR_VEC[] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
    pos_t npos = {
        out_tetro->pos.x + S_DIR_VEC[dir].x * 1,
        out_tetro->pos.y + S_DIR_VEC[dir].y * 1
    };
    tetromino_status_t res = check_tetromino_next_status(board, out_tetro, npos, out_tetro->rotate_dir);
    if (res == TETROMINO_STATUS_MOVED) {
        out_tetro->pos = npos;
        update_tetromino_ground_pos(board, out_tetro);
    }
    tetris_play_tetromino_unlock();
    return res;
}

tetromino_status_t try_rotate_tetromino_r(const tetris_play_board_t* board, tetromino_t* const out_tetro, int by)
{
    tetris_play_tetromino_lock();
    if (out_tetro->id == -1) {
        tetris_play_tetromino_unlock();
        return TETROMINO_STATUS_NULL;
    }
    dir_t nrotate_dir = (out_tetro->rotate_dir + by + TOTAL_DIR_NUM_OF_KINDS) % TOTAL_DIR_NUM_OF_KINDS;
    tetromino_status_t res = check_tetromino_next_status(board, out_tetro, out_tetro->pos, nrotate_dir);
    if (res == TETROMINO_STATUS_MOVED) {
        out_tetro->rotate_dir = nrotate_dir;
        update_tetromino_ground_pos(board, out_tetro);
    }
    tetris_play_tetromino_unlock();
    return res;    
}

void update_tetromino_ground_pos(const tetris_play_board_t* restrict board, tetromino_t* restrict const out_tetro)
{
    debug();

    for (pos_t cground_pos = out_tetro->pos; cground_pos.x < board->height; ++cground_pos.x) {
        pos_t nground_pos = { cground_pos.x + 1, cground_pos.y };
        tetromino_status_t res = check_tetromino_next_status(board, out_tetro, nground_pos, out_tetro->rotate_dir);
        if (res != TETROMINO_STATUS_MOVED) {
            out_tetro->ground_pos = cground_pos;
            return;
        }
    }
    my_assert(false);
}

tetromino_status_t harddrop_tetromino_r(tetromino_t* const out_tetro)
{
    tetris_play_tetromino_lock();
    my_assert(out_tetro->id != -1);
    out_tetro->pos = out_tetro->ground_pos;
    tetris_play_tetromino_unlock();
    return TETROMINO_STATUS_MOVED;
}
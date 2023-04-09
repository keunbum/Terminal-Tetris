#include <stdio.h>

#include "debug.h"
#include "draw/cursor.h"
#include "draw/draw_tool.h"
#include "tetris_play_update.h"

/* return tetromino's status when moving left, right, or down.
   implement the rotation operation separately. */

static tetromino_status_t check_tetromino_next_status(const game_board_t* board, const tetromino_t* tetro, pos_t npos)
{
    debug();

    const tetromino_symbol_t* symbol = G_TETROMINO_SYMBOLS + tetro->symbol_id;
    for (int i = 0; i < symbol->height; ++i) {
        const block_t* row = symbol->block_matrix[i];
        for (int j = 0; row[j]; ++j) {
            if (row[j] == BLOCK_T_FALSE) {
                continue;
            }
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
            game_board_grid_element_t each_value = board->grid[(int)each_npos.x][(int)each_npos.y];
            if (each_value != TETRIS_PLAY_BOARD_GRID_ELEMENT_DEFAULT && each_value != tetro->id) {
                ewprintf("hi3\n");
                return TETROMINO_STATUS_ONTHEGROUND;
            }
        }
    }
    ewprintf("hi4\n");
    return TETROMINO_STATUS_MOVED;
}

static tetromino_status_t new_check_tetromino_next_status(const game_board_t* board, const tetromino_t* tetro, pos_t npos)
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
        game_board_grid_element_t each_value = board->grid[(int)each_npos.x][(int)each_npos.y];
        if (each_value != TETRIS_PLAY_BOARD_GRID_ELEMENT_DEFAULT && each_value != tetro->id) {
            ewprintf("hi3\n");
            return TETROMINO_STATUS_ONTHEGROUND;
        }                       
    }
    ewprintf("hi4\n");
    return TETROMINO_STATUS_MOVED;    
}

static tetromino_status_t move_tetromino_mainbody(const game_board_t* board, tetromino_t* const out_tetro)
{
    debug();

    static const pos_t S_POS_D[] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
    pos_t npos = {
        out_tetro->pos.x + (pos_e_t)(out_tetro->velocity * 1) * S_POS_D[out_tetro->rotate_dir].x,
        out_tetro->pos.y + (pos_e_t)(out_tetro->velocity * 1) * S_POS_D[out_tetro->rotate_dir].y
    };
    tetromino_status_t res = check_tetromino_next_status(board, out_tetro, npos);
    if (res == TETROMINO_STATUS_MOVED) {
        out_tetro->pos = npos;
    }
    return res;
}

static tetromino_status_t new_move_tetromino_mainbody(const game_board_t* board, tetromino_t* const out_tetro, dir_t dir)
{
    debug();

    // hmm...
    static const pos_t S_DIR_VEC[] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
    pos_t npos = {
        out_tetro->pos.x + (pos_e_t)(out_tetro->velocity * 1) * S_DIR_VEC[dir].x,
        out_tetro->pos.y + (pos_e_t)(out_tetro->velocity * 1) * S_DIR_VEC[dir].y
    };
    tetromino_status_t res = new_check_tetromino_next_status(board, out_tetro, npos);
    if (res == TETROMINO_STATUS_MOVED) {
        out_tetro->pos = npos;
    }
    return res;
}

// static void move_a_tetromino_expected(game_board_t* const board, tetromino_t* const out_tetro)
// {
// }

// static void new_move_a_tetromino_expected(game_board_t* const board, tetromino_t* const out_tetro)
// {
// }

tetromino_status_t move_tetromino(const game_board_t* board, tetromino_t* const out_tetro)
{
    debug();

    tetromino_status_t res = move_tetromino_mainbody(board, out_tetro);
    // move_a_tetromino_expected(board, out_tetro);
    return res;
}

static tetromino_status_t new_move_tetromino(const game_board_t* board, tetromino_t* const out_tetro, dir_t dir)
{
    debug();

    tetromino_status_t res = new_move_tetromino_mainbody(board, out_tetro, dir);
    // new_move_a_tetromino_expected(board, out_tetro);
    return res;
}

tetromino_status_t new_move_tetromino_down(const game_board_t* board, tetromino_t* const out_tetro)
{
    debug();

    return new_move_tetromino(board, out_tetro, DIR_BOT);
}

void petrity_tetromino(game_board_t* const out_board, const tetromino_t* tetro)
{
    debug();

    const tetromino_symbol_t* symbol = G_TETROMINO_SYMBOLS + tetro->symbol_id;
    for (int i = 0; i < symbol->height; ++i) {
        const block_t* row = symbol->block_matrix[i];
        for (int j = 0; row[j]; ++j) {
            if (row[j] == BLOCK_T_FALSE) {
                continue;
            }
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
}

void new_petrity_tetromino(game_board_t* const out_board, const tetromino_t* tetro)
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

bool is_at_skyline(const tetromino_t* tetro)
{
    debug();

    my_assert(0 <= tetro->symbol_id && tetro->symbol_id < TOTAL_TETROMINO_NUM_OF_KINDS);
    const tetromino_symbol_t* symbol = G_TETROMINO_SYMBOLS + tetro->symbol_id;
    return tetro->pos.x + symbol->height <= 0;
}

bool new_is_at_skyline(const tetromino_t* tetro)
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

void update_tetromino_ground_pos(const game_board_t* restrict board, tetromino_t* restrict const out_tetro)
{
    debug();

    for (pos_t cground_pos = out_tetro->pos; cground_pos.x < board->height; ++cground_pos.x) {
        pos_t nground_pos = { cground_pos.x + 1, cground_pos.y };
        tetromino_status_t res = check_tetromino_next_status(board, out_tetro, nground_pos);
        if (res != TETROMINO_STATUS_MOVED) {
            out_tetro->ground_pos = cground_pos;
            return;
        }
    }
    my_assert(false);
}

void new_update_tetromino_ground_pos(const game_board_t* restrict board, tetromino_t* restrict const out_tetro)
{
    debug();

    for (pos_t cground_pos = out_tetro->pos; cground_pos.x < board->height; ++cground_pos.x) {
        pos_t nground_pos = { cground_pos.x + 1, cground_pos.y };
        tetromino_status_t res = new_check_tetromino_next_status(board, out_tetro, nground_pos);
        if (res != TETROMINO_STATUS_MOVED) {
            out_tetro->ground_pos = cground_pos;
            return;
        }
    }
    my_assert(false);
}

// void try_rotate_tetromino_counterclockwise(game_board_t* const, tetromino_t* const)
// {
    
// }

// void try_rotate_tetromino_clockwise(game_board_t* const, tetromino_t* const)
// {

// }


/* ------------------------------------------------------------------------------------------------------------------------------------------- */

// /* return tetromino's status when moving left, right, or down.
//    implement the rotation operation separately. */
// tetromino_status_t new_move_a_tetromino(game_board_t* const board, tetromino_t* const out_tetro, double game_delta_time)
// {
//     debug();

//     static const pos_int_t S_POS_D[] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

//     pos_t npos = {
//         out_tetro->pos.x + (out_tetro->velocity * game_delta_time) * S_POS_D[out_tetro->rotate_dir].x,
//         out_tetro->pos.y + (out_tetro->velocity * game_delta_time) * S_POS_D[out_tetro->rotate_dir].y,
//     };
//     const tetromino_symbol_t* symbol = G_TETROMINO_SYMBOLS + out_tetro->symbol_id;
//     for (int i = 0; i < symbol->height; ++i) {
//         const block_t* row = symbol->block_matrix[i];
//         for (int j = 0; row[j]; ++j) {
//             if (row[j] == BLOCK_T_FALSE) {
//                 continue;
//             }
//             // pos_int_t each_npos = { (int)npos.x + i, (int)npos.y + j };
//             pos_int_t each_npos = { (int)(npos.x + i), (int)(npos.y + j) };
//             my_assert(each_npos.x >= TETRIS_PLAY_TETROMINO_POS_X_MIN);
//             if (each_npos.y < TETRIS_PLAY_TETROMINO_POS_Y_MIN || each_npos.y > TETRIS_PLAY_TETROMINO_POS_Y_MAX) {
//                 ewprintf("hi1\n");
//                 return TETROMINO_STATUS_INPLACE;
//             }
//             if (each_npos.x > TETRIS_PLAY_TETROMINO_POS_X_MAX) {
//                 ewprintf("hi2\n");
//                 return TETROMINO_STATUS_ONTHEGROUND;
//             }
//             if (each_npos.x < 0) {
//                 continue;
//             }
//             my_assert(each_npos.x >= 0);
//             my_assert(each_npos.x < TETRIS_PLAY_BOARD_HEIGHT);
//             my_assert(0 <= each_npos.y && each_npos.y < TETRIS_PLAY_BOARD_WIDTH);
//             game_board_grid_element_t each_value = board->grid[(int)each_npos.x][(int)each_npos.y];
//             if (each_value != TETRIS_PLAY_BOARD_GRID_ELEMENT_DEFAULT && each_value != out_tetro->id) {
//                 ewprintf("hi3\n");
//                 return TETROMINO_STATUS_ONTHEGROUND;
//             }
//         }
//     }
//     out_tetro->pos = npos;
//     ewprintf("hi4\n");
//     return TETROMINO_STATUS_MOVED;
// }
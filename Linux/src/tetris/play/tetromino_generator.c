#include <stdbool.h>

#include "debug.h"
#include "mt19937.h"
#include "tetromino_generator.h"

static tetromino_id_t g_s_tetromino_spawned_cnt;

static bool is_tetromino_y_in_board(const game_board_t* board, const tetromino_t* tetro, pos_e_t pos_y)
{
    debug();

    const tetromino_symbol_t* symbol = G_TETROMINO_SYMBOLS + tetro->symbol_id;
    for (int i = 0; i < symbol->height; ++i) {
        const block_t* row = symbol->block_matrix[i];
        for (int j = 0; row[j]; ++j) {
            if (row[j] == BLOCK_T_FALSE) {
                continue;
            }
            pos_e_t each_pos_y = pos_y + j;
            if (each_pos_y < 0 || each_pos_y >= board->width) {
                return false;
            }
        }
    }
    return true;
}

static pos_e_t get_pos_y_random(const game_board_t* board, const tetromino_t* tetro)
{
    debug();

    pos_e_t pos_y;
    do {
        pos_y = (pos_e_t)(rng() % board->width);
    } while (!is_tetromino_y_in_board(board, tetro, pos_y));
    return pos_y;
}

void init_tetromino_generator(void)
{
    debug();

    g_s_tetromino_spawned_cnt = 1;
}

void spawn_tetromino(const game_board_t* restrict board, tetromino_t* restrict const out_tetro)
{
    debug();

    out_tetro->id = g_s_tetromino_spawned_cnt++;
    out_tetro->symbol_id = (symbol_id_t)(rng() % TOTAL_TETROMINO_NUM_OF_KINDS);
    out_tetro->pos.x = TETRIS_PLAY_TETROMINO_INIT_POS_X;
    out_tetro->pos.y = get_pos_y_random(board, out_tetro);
    out_tetro->velocity = TETRIS_PLAY_TETROMINO_INIT_VELOCITY;
    out_tetro->rotate_dir = DIR_BOT;
    out_tetro->block_code = G_BLOCK_CODE_SET->codes[get_block_code_fixed(out_tetro->symbol_id, G_BLOCK_CODE_SET->size)];
}

void new_spawn_tetromino(const game_board_t* restrict board, tetromino_t* restrict const out_tetro)
{
    debug();

    out_tetro->id = g_s_tetromino_spawned_cnt++;
    out_tetro->symbol_id = (symbol_id_t)(rng() % TOTAL_TETROMINO_NUM_OF_KINDS);
    out_tetro->pos.x = TETRIS_PLAY_TETROMINO_INIT_POS_X;
    out_tetro->pos.y = get_pos_y_random(board, out_tetro);
    out_tetro->velocity = TETRIS_PLAY_TETROMINO_INIT_VELOCITY;
    out_tetro->rotate_dir = (dir_t)(rng() % TOTAL_DIR_NUM_OF_KINDS);
    out_tetro->block_code = G_BLOCK_CODE_SET->codes[get_block_code_fixed(out_tetro->symbol_id, G_BLOCK_CODE_SET->size)];
}
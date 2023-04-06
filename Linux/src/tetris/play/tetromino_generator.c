#include <time.h>

#include "debug.h"
#include "random.h"
#include "tetromino_generator.h"

static tetromino_id_t g_s_tetromino_spawned_cnt;

void init_tetromino_generator(void)
{
    debug();

    init_rng((unsigned int)time(NULL));
    g_s_tetromino_spawned_cnt = 1;
}

void new_spawn_tetromino(tetromino_t* const out_tetro)
{
    debug();

    symbol_id_t symbol_id = (int)(rng() % TOTAL_TETROMINO_NUM_OF_KINDS);
    pos_t pos = { TETRIS_PLAY_TETROMINO_INIT_POS_X, TETRIS_PLAY_TETROMINO_INIT_POS_Y };
    tetromino_id_t tetromino_id = g_s_tetromino_spawned_cnt++;
    init_a_tetromino(
        out_tetro,
        tetromino_id,
        symbol_id,
        pos,
        NEW_TETRIS_PLAY_TETROMINO_INIT_VELOCITY,
        DIR_BOT,
        G_BLOCK_CODE_SET->codes[get_block_code_fixed(symbol_id, G_BLOCK_CODE_SET->size)]);
}

void spawn_tetromino(tetromino_t* const out_tetro)
{
    debug();

    symbol_id_t symbol_id = (int)(rng() % TOTAL_TETROMINO_NUM_OF_KINDS);
    pos_t pos = { TETRIS_PLAY_TETROMINO_INIT_POS_X, TETRIS_PLAY_TETROMINO_INIT_POS_Y };
    tetromino_id_t tetromino_id = g_s_tetromino_spawned_cnt++;
    init_a_tetromino(
        out_tetro,
        tetromino_id,
        symbol_id,
        pos,
        TETRIS_PLAY_TETROMINO_INIT_VELOCITY,
        DIR_BOT,
        G_BLOCK_CODE_SET->codes[get_block_code_fixed(symbol_id, G_BLOCK_CODE_SET->size)]);
}
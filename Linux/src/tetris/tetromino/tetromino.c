#include <time.h>

#include "debug.h"
#include "random.h"
#include "tetromino.h"
#include "block_code_set.h"

static tetromino_id_t g_s_tetromino_spawned_cnt;

const tetromino_symbol_t G_TETROMINO_SYMBOLS[TOTAL_TETROMINO_NUM_OF_KINDS] = {
    // I
    {
        1,
        {
            "1111",
        },
    },
    // O
    {
        2,
        {
            "11",
            "11",
        },
    },
    // T
    {
        2,
        {
            "010",
            "111",
        },
    },
    // J
    {
        2,
        {
            "100",
            "111",
        },
    },
    // L
    {
        2,
        {
            "001",
            "111",
        },
    },
    // S
    {
        2,
        {
            "011",
            "110",
        },
    },
    // Z
    {
        2,
        {
            "110",
            "011",
        },
    },
};

void init_a_tetromino(tetromino_t* const out_tetro, symbol_id_t symbol_id, pos_t pos, velocity_t velocity, dir_t dir, wchar_t block_code)
{
    debug();

    out_tetro->id = g_s_tetromino_spawned_cnt++;
    out_tetro->symbol_id = symbol_id;
    out_tetro->pos = pos;
    out_tetro->velocity = velocity;
    out_tetro->dir = dir;
    out_tetro->block_code = block_code;
}

void init_tetromino_generator(void)
{
    debug();

    init_rng((unsigned int)time(NULL));
    g_s_tetromino_spawned_cnt = 1;
}

void spawn_a_tetromino(tetromino_t* const out_tetro, pos_t pos, velocity_t velocity)
{
    symbol_id_t symbol_id = (int)(rng() % TOTAL_TETROMINO_NUM_OF_KINDS);
    const block_code_set_t* code_set = G_BLOCK_CODE_SET_DEFAULT;
    init_a_tetromino(
        out_tetro,
        symbol_id,
        pos,
        velocity,
        DIR_BOT,
        code_set->codes[get_block_code_fixed(code_set, symbol_id)]);
}
#include "tetromino.h"
#include "debug.h"

static tetromino_id_t g_s_tetromino_cnt;

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

int encode_block_t(block_t block)
{
    debug();

    return (int)(block - '1');
}

void init_tetromino_generator(void)
{
    debug();

    g_s_tetromino_cnt = 1;
}

void init_a_tetromino(tetromino_t* const out_t, symbol_id_t symbol_id, pos_t pos_x, pos_t pos_y, velocity_t velocity, dir_t dir, wchar_t block_code)
{
    debug();

    out_t->id = g_s_tetromino_cnt++;
    out_t->symbol_id = symbol_id;
    out_t->pos_x = pos_x;
    out_t->pos_y = pos_y;
    out_t->velocity = velocity;
    out_t->dir = dir;
    out_t->block_code = block_code;
}
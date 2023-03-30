#include "tetromino.h"
#include "debug/debug.h"

static tetromino_id_t g_s_tetromino_ptr;

const tetromino_symbol_t G_TETROMINO_SYMBOLS[TOTAL_TETROMINO_NUM] = {
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
            "111",
            "010",
        },
    },
    // J
    {
        3,
        {
            "01",
            "01",
            "11",
        },
    },
    // L
    {
        3,
        {
            "10",
            "10",
            "11",
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

int encode_block(block_t ch)
{
    debug();

    return (int)(ch - '1');
}

void init_tetromino_generator(void)
{
    debug();

    g_s_tetromino_ptr = 1;
}

void init_tetromino(tetromino_t* const out_t, int symbol_id, pos_t pos_x, pos_t pos_y, unsigned int velocity, dir_t dir, wchar_t block_code)
{
    debug();
    
    out_t->id = g_s_tetromino_ptr++;
    out_t->symbol_id = symbol_id;
    out_t->pos_x = pos_x;
    out_t->pos_y = pos_y;
    out_t->velocity = velocity;
    out_t->dir = dir;
    out_t->block_code = block_code;
}
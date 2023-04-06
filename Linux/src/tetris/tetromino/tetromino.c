#include <time.h>

#include "block_code_set.h"
#include "debug.h"
#include "tetromino.h"

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

void init_a_tetromino(tetromino_t* const out_tetro, tetromino_id_t id, symbol_id_t symbol_id, pos_t pos, velocity_t velocity, dir_t dir, wchar_t block_code)
{
    debug();
    ewprintf("init tetromino.pos: (%lf, %lf)\n", pos.x, pos.y);

    out_tetro->id = id;
    out_tetro->symbol_id = symbol_id;
    out_tetro->pos = pos;
    out_tetro->velocity = velocity;
    out_tetro->dir = dir;
    out_tetro->block_code = block_code;
}

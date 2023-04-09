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

const polyomino_matrix_n_t G_TETROMINO_MATRIX_NS[TOTAL_TETROMINO_NUM_OF_KINDS] = {
    4, 2, 3, 3, 3, 3, 3
};

const polyomino_matrix_t G_TETROMINO_MATRIXS[TOTAL_TETROMINO_NUM_OF_KINDS][TOTAL_DIR_NUM_OF_KINDS] = {
    { 0x00F0, 0x2222, 0x0F00, 0x4444 }, // I
    { 0x000F, 0x000F, 0x000F, 0x000F }, // O
    { 0x003A, 0x009A, 0x00B8, 0x00B2 }, // T
    { 0x01C8, 0x01A4, 0x0027, 0x004B }, // J
    { 0x01E0, 0x0126, 0x000F, 0x00C9 }, // L
    { 0x00F0, 0x0132, 0x001E, 0x0099 }, // S
    { 0x0198, 0x00B4, 0x0033, 0x005A }, // Z
};

// void init_a_tetromino(tetromino_t* const out_tetro, tetromino_id_t id, symbol_id_t symbol_id, pos_t pos, velocity_t velocity, dir_t rotate_dir, wchar_t block_code)
// {
//     debug();

//     out_tetro->id = id;
//     out_tetro->symbol_id = symbol_id;
//     out_tetro->pos = pos;
//     out_tetro->velocity = velocity;
//     out_tetro->rotate_dir = rotate_dir;
//     out_tetro->block_code = block_code;
// }

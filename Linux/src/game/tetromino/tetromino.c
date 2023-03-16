#include "game/tetromino/tetromino.h"

const tetromino_symbol_t g_tetromino_symbols[TOTAL_TETROMINO_NUM] = {
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

int encode_block(char ch)
{
    return (int) (ch - '1');
}

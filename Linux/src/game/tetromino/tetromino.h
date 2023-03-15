#ifndef __TETROMINO__H
#define __TETROMINO__H

#include <wchar.h>

#include "block.h"
#include "color.h"

#define DECLARE_POLYOMINO_SYMBOL_T(T)   \
    typedef struct polyomino_symbol_##T \
    {                                   \
        int height;                     \
        block_t *grid[T];               \
    } polyomino_symbol_##T##_t

DECLARE_POLYOMINO_SYMBOL_T(4);

typedef polyomino_symbol_4_t tetromino_symbol_t;

#define TOTAL_TETROMINO_NUM (7)
static const tetromino_symbol_t s_tetromino_symbols[TOTAL_TETROMINO_NUM] = {
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

typedef enum dir
{
    DIR_BOT,
} dir_t;

typedef struct tetromino
{
    int tetromino_id;
    int x;
    int y;
    int velocity;
    //    int acceleration;
    dir_t dir;
    color_t color;
} tetromino_t;

int encode_block(char);

#endif /* __TETROMINO__H */
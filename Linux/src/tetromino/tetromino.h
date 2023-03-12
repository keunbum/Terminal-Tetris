#ifndef __TETROMINO__H
#define __TETROMINO__H

#include <wchar.h>

#include "block.h"
#include "color.h"

#define DECLARE_POLYOMINO_SYMBOL_T(T) \
    typedef struct polyomino_symbol_##T       \
    {                                 \
        block_t *blocks2d[T];         \
    } polyomino_symbol_##T##_t

DECLARE_POLYOMINO_SYMBOL_T(4);

//#define TETROMINO_MAX_VER_BLOCK_LEN (4)
#define TOTAL_TETROMINO_NUM (7)

typedef polyomino_symbol_4_t tetromino_symbol_t;

static const tetromino_symbol_t s_tetromino_symbols[TOTAL_TETROMINO_NUM] = {
    // I
    {
        {
            "1111",
        },
    },
    // O
    {
        {
            "11",
            "11",
        },
    },
    // T
    {
        {
            "111",
            "010",
        },
    },
    // J
    {
        {
            "01",
            "01",
            "11",
        },
    },
    // L
    {
        {
            "10",
            "10",
            "11",
        },
    },
    // S
    {
        {
            "011",
            "110",
        },
    },
    // Z
    {
        {
            "110",
            "011",
        },
    },
};

typedef enum dir {
    DIR_BOT,
} dir_t;

typedef struct tetromino {
    int tetromino_id;
    int x;
    int y;
    int velocity;
//    int acceleration;
    dir_t dir;
    color_t color;
} tetromino_t;

void print_tetromino(const tetromino_t *);

#define print_empty_line draw_empty_line

#endif /* __TETROMINO__H */
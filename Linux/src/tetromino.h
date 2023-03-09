#ifndef __TETROMINO__H
#define __TETROMINO__H

#include <wchar.h>

#include "block.h"
#include "color.h"

#define MAX_HOR_BLOCK_LEN (4)
#define MAX_VER_BLOCK_LEN (4)

#define TETROMINO_COUNT (7)

typedef struct polyomino
{
    block_t *block2d[MAX_VER_BLOCK_LEN];
} polyomino_t;

static const polyomino_t s_tetrominos[TETROMINO_COUNT] = {
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
        }
    },
    // T
    {
        {
            "111",
            "010",
        }
    },
    // J
    {
        {
            "01",
            "01",
            "11",
        }
    },
    // L
    {
        {
            "10",
            "10",
            "11",
        }
    },
    // S
    {
        {
            "011",
            "110",
        }
    },
    // Z
    {
        {
            "110",
            "011",
        }
    },
};

typedef enum dir
{
    DIR_BOT,
} dir_t;

typedef struct tetromino
{
    int polyomino_id;
    dir_t dir;
    color_t color;
} tetromino_t;

void print_tetromino(const tetromino_t *);
void print_a_block(wchar_t);
void print_full_block(void);
void print_empty_block(void);

#endif /* __TETROMINO__H */
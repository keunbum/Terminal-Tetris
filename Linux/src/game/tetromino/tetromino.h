#ifndef __TETROMINO__H
#define __TETROMINO__H

#include "block.h"
#include "color.h"

#define DECLARE_POLYOMINO_SYMBOL_T(T)                                         \
  typedef struct polyomino_symbol_##T {                                       \
    int height;                                                               \
    block_t *grid[T];                                                         \
  } polyomino_symbol_##T##_t

DECLARE_POLYOMINO_SYMBOL_T(4);

typedef polyomino_symbol_4_t tetromino_symbol_t;

#define TOTAL_TETROMINO_NUM (7)

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

extern const tetromino_symbol_t g_tetromino_symbols[TOTAL_TETROMINO_NUM];

int encode_block(char);

#endif /* __TETROMINO__H */
#ifndef __TETROMINO__H
#define __TETROMINO__H

#include "block.h"
#include "color.h"
#include "polyomino.h"
#include "pos.h"

DECLARE_POLYOMINO_SYMBOL_T(4);

typedef polyomino_symbol_4_t tetromino_symbol_t;

typedef enum {
    DIR_BOT = 0,
    DIR_LEFT = 1,
    DIR_RIGHT = 2,
} dir_t;

typedef int tetromino_id_t;
typedef int symbol_id_t;
typedef unsigned int velocity_t;

typedef struct {
    tetromino_id_t id;
    symbol_id_t symbol_id;
    pos_t pos;
    velocity_t velocity;
    dir_t dir;
    wchar_t block_code;
} tetromino_t;

#define TOTAL_TETROMINO_NUM_OF_KINDS (7)

extern const tetromino_symbol_t G_TETROMINO_SYMBOLS[TOTAL_TETROMINO_NUM_OF_KINDS];

void init_a_tetromino(tetromino_t* const, tetromino_id_t, symbol_id_t, pos_t, velocity_t, dir_t, wchar_t);

#endif /* __TETROMINO__H */

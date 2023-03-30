#ifndef __TETROMINO__H
#define __TETROMINO__H

#include "block.h"
#include "color.h"

#define DECLARE_POLYOMINO_SYMBOL_T(T) \
    typedef struct {                  \
        int height;                   \
        block_t* grid[T];             \
    } polyomino_symbol_##T##_t

DECLARE_POLYOMINO_SYMBOL_T(4);

typedef polyomino_symbol_4_t tetromino_symbol_t;

typedef enum {
    DIR_BOT = 0,
    DIR_LEFT = 1,
    DIR_RIGHT = 2,
} dir_t;

typedef int pos_t;
typedef int tetromino_id_t;
typedef int symbol_id_t;

typedef struct {
    tetromino_id_t id;
    symbol_id_t symbol_id;
    pos_t pos_x;
    pos_t pos_y;
    unsigned int velocity;
    //    int acceleration;
    dir_t dir;
    wchar_t block_code;
    //    color_t color;
} tetromino_t;

#define TOTAL_TETROMINO_NUM (7)

extern const tetromino_symbol_t G_TETROMINO_SYMBOLS[TOTAL_TETROMINO_NUM];

int encode_block(char);
void init_tetromino_generator(void);
void init_tetromino(tetromino_t* const, int, pos_t, pos_t, unsigned int, dir_t, wchar_t);

#endif /* __TETROMINO__H */

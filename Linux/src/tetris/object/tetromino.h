#ifndef __TETROMINO__H
#define __TETROMINO__H

#include <stdbool.h>
#include <stdlib.h>

#include "block.h"
#include "block_wprint.h"
#include "debug.h"
#include "pos.h"
#include "util.h"

typedef int tetromino_shape_t;

typedef enum {
    DIR_BOT,
    DIR_RIGHT,
    DIR_TOP,
    DIR_LEFT,
} dir_t;
#define TETROMINO_INIT_DIR (DIR_BOT)
#define DIR_NUM_OF_KINDS (4)

typedef int shape_id_t;
typedef float velocity_t;
typedef struct tetromino tetromino_t;

struct tetromino {
    shape_id_t shape_id;
    dir_t dir;
    pos_t pos;
    pos_t pos_wprint;
    velocity_t velocity;
    block_t block;
    block_wprint_t clean_wprint;
    tetromino_t* prev_drawn;
};
#define TETROMINO_NUM_OF_KINDS (7)

extern const tetromino_shape_t G_TETROMINO_SYMBOLS[TETROMINO_NUM_OF_KINDS][DIR_NUM_OF_KINDS];

/* -----------------------------------------------------------------------------------------*/

static inline bool is_mino(tetromino_shape_t m, int pos)
{
    return (m >> pos) & 1;
}

#define traverse_shape(i, j, shape) \
    for (int i = 0; i < 4; ++i)       \
        for (int j = 0; j < 4; ++j)   \
            if (is_mino(shape, i * 4 + j))

static inline bool is_valid_tetromino(const tetromino_t* tetro)
{
    return tetro != NULL;
}

static inline bool is_first_drawn_tetromino(const tetromino_t* tetro)
{
    my_assert(tetro != NULL);

    return !is_valid_tetromino(tetro->prev_drawn);
}

static inline tetromino_shape_t get_tetromino_shape(shape_id_t shape_id, dir_t dir)
{
    return G_TETROMINO_SYMBOLS[shape_id][dir];
}

const wchar_t* get_dir_wstr(dir_t dir);
wchar_t get_shape_wch(shape_id_t shape_id);
void save_tetromino_tobedrawn(tetromino_t* const out_tetro);
void cleanup_tetromino_free(tetromino_t* const out_tetro);
tetromino_t* init_tetromino_malloc(shape_id_t shape_id, dir_t dir, pos_t pos, velocity_t velocity, block_t block, block_wprint_t clean_wprint, tetromino_t* prev_drawn);
tetromino_t* init_tetromino_poswprint_malloc(shape_id_t shape_id, dir_t dir, pos_t pos_wprint, velocity_t velocity, block_t block, block_wprint_t clean_wprint, tetromino_t* prev_drawn);

#ifdef TETRIS_DEBUG
static inline void debug_tetromino(const tetromino_t* tetro)
{
    ewprintf("shape: %lc\n", get_shape_wch(tetro->shape_id));
    ewprintf("dir: %ls\n", get_dir_wstr(tetro->dir));
    ewprintf("pos: (%d, %d)\n", (int)tetro->pos.x, (int)tetro->pos.y);
}
#endif

#endif /* __TETROMINO__H */

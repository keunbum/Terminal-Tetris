#ifndef __TETROMINO__H
#define __TETROMINO__H

#include <pthread.h>
#include <stdbool.h>

#include "block.h"
#include "block_wprint.h"
#include "debug.h"
#include "pos.h"
#include "tetris_play_object.h"
#include "util.h"

typedef int tetromino_matrix_t;
typedef int tetromino_matrix_n_t;

static inline bool is_empty_block(tetromino_matrix_t m, int pos)
{
    return ((m >> pos) & 1) == 0;
}

typedef enum {
    DIR_BOT,
    DIR_RIGHT,
    DIR_TOP,
    DIR_LEFT,
} dir_t;
#define TETROMINO_INIT_DIR (DIR_BOT)

typedef int symbol_id_t;
typedef double velocity_t;

typedef struct tetromino_t tetromino_t;
struct tetromino_t {
    symbol_id_t symbol_id; // 0-based
    pos_t pos;
    dir_t dir;
    velocity_t velocity;
    block_t block;

    tetromino_t* prev_drawn;
    // updatable_func_t update;
    // drawable_func_t draw;
};
#define TETROMINO_NUM_OF_KINDS (7)
#define DIR_NUM_OF_KINDS (4)

extern const tetromino_matrix_n_t G_TETROMINO_MATRIX_NS[TETROMINO_NUM_OF_KINDS];
extern const tetromino_matrix_t G_TETROMINO_MATRIXS[TETROMINO_NUM_OF_KINDS][DIR_NUM_OF_KINDS];

/* -----------------------------------------------------------------------------------------*/

static inline bool is_first_drawn_tetromino(const tetromino_t* tetro)
{
    return tetro->prev_drawn == NULL;
}

static inline bool is_valid_tetromino(const tetromino_t* tetro)
{
    return tetro != NULL;
}

static inline tetromino_matrix_n_t get_tetromino_matrix_n(symbol_id_t sid)
{
    return G_TETROMINO_MATRIX_NS[(int)sid];
}

static inline tetromino_matrix_t get_tetromino_matrix(symbol_id_t sid, dir_t dir)
{
    my_assert(0 <= sid && sid < TETROMINO_NUM_OF_KINDS);
    my_assert(0 <= dir && dir < DIR_NUM_OF_KINDS);

    return G_TETROMINO_MATRIXS[(int)sid][(int)dir];
}

static inline pos_t get_tetromino_pos(const tetromino_t* tetro)
{
    return tetro->pos;
}

static inline void set_tetromino_pos(tetromino_t* const out_tetro, pos_t pos)
{
    out_tetro->pos = pos;
}

static inline dir_t get_tetromino_dir(const tetromino_t* tetro)
{
    return tetro->dir;
}

static inline void set_tetromino_dir(tetromino_t* const out_tetro, dir_t dir)
{
    out_tetro->dir = dir;
}

// void init_tetromino(tetromino_t* const out_tetro, symbol_id_t symbol_id, pos_t pos, dir_t dir, velocity_t velocity, block_t block, tetromino_t* prev_drawn);
// void cleanup_tetromino(tetromino_t* const out_tetro);

tetromino_t* init_tetromino_malloc(symbol_id_t symbol_id, pos_t pos, dir_t dir, velocity_t velocity, block_t block, tetromino_t* prev_drawn);
void cleanup_tetromino_free(tetromino_t* tetro);

#endif /* __TETROMINO__H */

#ifndef __TETROMINO__H
#define __TETROMINO__H

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

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
typedef float velocity_t;

typedef struct tetromino_t tetromino_t;
struct tetromino_t {
    int id; // for debug
    symbol_id_t symbol_id;
    dir_t dir;
    pos_t pos;
    pos_t pos_wprint;
    velocity_t velocity;
    block_t block;
    tetromino_t* prev_drawn;
};
#define TETROMINO_NUM_OF_KINDS (7)
#define DIR_NUM_OF_KINDS (4)

extern const tetromino_matrix_n_t G_TETROMINO_MATRIX_NS[TETROMINO_NUM_OF_KINDS];
extern const tetromino_matrix_t G_TETROMINO_MATRIXS[TETROMINO_NUM_OF_KINDS][DIR_NUM_OF_KINDS];

/* -----------------------------------------------------------------------------------------*/

static inline bool is_first_drawn_tetromino(const tetromino_t* tetro)
{
    my_assert(tetro != NULL);

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

static inline tetromino_t* create_tetromino_empty_malloc(void)
{
    return (tetromino_t*)malloc(sizeof(tetromino_t));
}

static inline void save_tetromino_tobedrawn(tetromino_t* const out_tetro, block_wprint_t clean_wprint)
{
    debug();
    
    my_assert(out_tetro != NULL);

    if (out_tetro->prev_drawn == NULL) {
        out_tetro->prev_drawn = create_tetromino_empty_malloc();
    }
    out_tetro->prev_drawn->id = out_tetro->id;
    out_tetro->prev_drawn->symbol_id = out_tetro->symbol_id;
    out_tetro->prev_drawn->dir = out_tetro->dir;
    out_tetro->prev_drawn->pos = out_tetro->pos;
    out_tetro->prev_drawn->pos_wprint = out_tetro->pos_wprint;
    out_tetro->prev_drawn->block = create_block(BLOCK_NATURE_EMPTY, clean_wprint);
}

// void init_tetromino(tetromino_t* const out_tetro, symbol_id_t symbol_id, pos_t pos, dir_t dir, velocity_t velocity, block_t block, tetromino_t* prev_drawn);
// void cleanup_tetromino(tetromino_t* const out_tetro);

tetromino_t* init_tetromino_malloc(int id, symbol_id_t symbol_id, dir_t dir, pos_t pos, velocity_t velocity, block_t block, tetromino_t* prev_drawn);
tetromino_t* init_tetromino_poswprint_malloc(int id, symbol_id_t symbol_id, dir_t dir, pos_t pos_wprint, velocity_t velocity, block_t block, tetromino_t* prev_drawn);
void cleanup_tetromino_free(tetromino_t** tetro);

#endif /* __TETROMINO__H */

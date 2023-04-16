#ifndef __TETRIS_PLAY_TETROMINO_GENERATOR__H
#define __TETRIS_PLAY_TETROMINO_GENERATOR__H

#include "tetris/object/block_wprint_set.h"
#include "tetris/object/tetromino.h"

typedef struct {
    const block_wprint_set_t* block_wprint_set;
} tetromino_generator_t;

static inline const block_wprint_set_t* get_block_wprint_set(const tetromino_generator_t* tetro_gen)
{
    my_assert(tetro_gen->block_wprint_set != NULL);

    return tetro_gen->block_wprint_set;
}

void init_tetromino_generator(tetromino_generator_t* const out_gen);
tetromino_t* spawn_tetromino_malloc(pos_t init_pos, velocity_t init_velocity);

#endif /* __TETRIS_PLAY_TETROMINO_GENERATOR__H */
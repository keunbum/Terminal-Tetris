#ifndef __TETRIS_PLAY_TETROMINO_GENERATOR__H
#define __TETRIS_PLAY_TETROMINO_GENERATOR__H

#include "tetris/object/block_wprint_set.h"
#include "tetris/object/tetromino.h"

typedef struct {
    int spawnd_cnt;
    const block_wprint_set_t* block_wprint_set;
    int ptr;
    symbol_id_t symbols[TETROMINO_NUM_OF_KINDS];
} tetromino_generator_t;

static inline const block_wprint_set_t* get_block_wprint_set(const tetromino_generator_t* tetro_gen)
{
    my_assert(tetro_gen->block_wprint_set != NULL);

    return tetro_gen->block_wprint_set;
}

void init_tetromino_generator(tetromino_generator_t* const out_gen);
void cleanup_tetromino_generator(tetromino_generator_t* const out_gen);
tetromino_t* create_tetromino_random_malloc(tetromino_generator_t* const out_gen, pos_t init_pos, velocity_t init_velocity, block_wprint_t init_clean_block);
tetromino_t* create_tetromino_symbol_poswprint_malloc(tetromino_generator_t* const out_gen, symbol_id_t init_symbol_id, pos_t init_pos_wprint, block_wprint_t init_clean_block);

#endif /* __TETRIS_PLAY_TETROMINO_GENERATOR__H */
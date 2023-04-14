#ifndef __TETRIS_PLAY_TETROMINO_GENERATOR__H
#define __TETRIS_PLAY_TETROMINO_GENERATOR__H

// #include "tetris/tetris_play_manager.h"
#include "tetris/object/block_wprint_set.h"
#include "tetris/object/tetromino.h"

typedef struct {
    int tetromino_spawned_cnt;
    const block_wprint_set_t* block_wprint_set;
} tetromino_generator_t;

static inline const block_wprint_set_t* get_block_wprint_set(const tetromino_generator_t* gen)
{
    my_assert(gen->block_wprint_set != NULL);
    
    return gen->block_wprint_set;
}

void new_init_tetromino_generator(tetromino_generator_t* const out_gen);
void new_spawn_tetromino(tetromino_generator_t* const restrict out_gen, tetromino_t* const restrict out_tetro, pos_t init_pos, velocity_t init_velocity);

// void init_tetromino_generator(void);
// void spawn_tetromino(tetris_play_manager_t* const restrict play_manager, tetromino_t* const restrict out_tetro, pos_t init_pos, velocity_t init_velocity);

#endif /* __TETRIS_PLAY_TETROMINO_GENERATOR__H */
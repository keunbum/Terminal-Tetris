#ifndef __TETRIS_PLAY_TETROMINO_GENERATOR__H
#define __TETRIS_PLAY_TETROMINO_GENERATOR__H

#include "tetris/tetris_play_manager.h"

void init_tetromino_generator(void);
// void spawn_tetromino(tetromino_t* restrict const out_tetro, pos_t init_pos, velocity_t init_velocity);
void new_spawn_tetromino(tetris_play_manager_t* const restrict play_manager, tetromino_t* const restrict out_tetro, pos_t init_pos, velocity_t init_velocity);

#endif /* __TETRIS_PLAY_TETROMINO_GENERATOR__H */
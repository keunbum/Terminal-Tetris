#ifndef __TETROMINO_GENERATOR__H
#define __TETROMINO_GENERATOR__H

#include "tetris/tetromino/tetromino.h"

void init_tetromino_generator(void);
void spawn_tetromino(tetromino_t* restrict const out_tetro, pos_t init_pos, velocity_t init_velocity);
// void spawn_tetromino_random(const tetris_play_board_t* restrict board, tetromino_t* restrict const out_tetro);

#endif /* __TETROMINO_GENERATOR__H */
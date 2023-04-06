#ifndef __TETROMINO_GENERATOR__H
#define __TETROMINO_GENERATOR__H

#include "tetris/play/tetris_play_board.h"
#include "tetris/tetromino/block_code_set.h"
#include "tetris/tetromino/tetromino.h"

void init_tetromino_generator(void);
void new_spawn_tetromino(tetromino_t* const);
void spawn_tetromino(tetromino_t* const);

#endif /* __TETROMINO_GENERATOR__H */
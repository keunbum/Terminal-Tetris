#ifndef __TETROMINO_GENERATOR__H
#define __TETROMINO_GENERATOR__H

#include "tetris/play/tetris_play_board.h"
#include "tetris/tetromino/block_code_set.h"
#include "tetris/tetromino/tetromino.h"

void init_tetromino_generator(void);
void spawn_tetromino(const game_board_t* restrict, tetromino_t* restrict const);

void new_spawn_tetromino(const game_board_t* restrict board, tetromino_t* restrict const out_tetro);

#endif /* __TETROMINO_GENERATOR__H */
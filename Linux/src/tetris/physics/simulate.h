#ifndef __SIMULATE__H
#define __SIMULATE__H

#include <stdbool.h>

#include "tetris/tetromino/tetromino.h"
#include "tetris/physics/game_board.h"

#define TETROMINO_STATUS_INPLACE (0)
#define TETROMINO_STATUS_MOVED (1)
#define TETROMINO_STATUS_ONTHEGROUND (2)

void erase_a_tetromino_r(const tetromino_t*);
void draw_a_tetromino_r(const tetromino_t*);
int move_a_tetromino(game_board_t* const, tetromino_t* const);
void petrity_tetromino(game_board_t* const, const tetromino_t*);
bool is_at_skyline(const tetromino_t*);

#endif /* __SIMULATE__H */
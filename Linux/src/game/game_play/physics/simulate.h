#ifndef __SIMULATE__H
#define __SIMULATE__H

#include "game/game_play/tetromino/tetromino.h"

#define TETROMINO_STATUS_INPLACE (0)
#define TETROMINO_STATUS_MOVED (1)
#define TETROMINO_STATUS_ONTHEGROUND (2)

void erase_tetromino_r(const tetromino_t* const);
void draw_tetromino_r(const tetromino_t* const);
int move_tetromino(tetromino_t* const);
void petrity_tetromino(const tetromino_t*);
bool is_at_skyline(const tetromino_t*);

#endif /* __SIMULATE__H */
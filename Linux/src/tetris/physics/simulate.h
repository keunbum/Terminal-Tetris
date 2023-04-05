#ifndef __SIMULATE__H
#define __SIMULATE__H

#include <stdbool.h>

#include "tetris/tetromino/tetromino.h"
#include "tetris/physics/tetris_play_board.h"

typedef enum {
    TETROMINO_STATUS_INPLACE,
    TETROMINO_STATUS_MOVED,
    TETROMINO_STATUS_ONTHEGROUND,
} tetromino_status_t;

void erase_a_tetromino_r(const tetromino_t*);
void draw_a_tetromino_r(const tetromino_t*);
tetromino_status_t move_a_tetromino(game_board_t* const, tetromino_t* const);
void petrity_tetromino(game_board_t* const, const tetromino_t*);
bool is_at_skyline(const tetromino_t*);

#endif /* __SIMULATE__H */
#ifndef __SIMULATE__H
#define __SIMULATE__H

#include <stdbool.h>

#include "tetris/tetromino/tetromino.h"
#include "tetris_play_board.h"

typedef enum {
    TETROMINO_STATUS_INPLACE,
    TETROMINO_STATUS_MOVED,
    TETROMINO_STATUS_ONTHEGROUND,
} tetromino_status_t;

tetromino_status_t move_a_tetromino(const game_board_t*, tetromino_t* const);
// tetromino_status_t new_move_a_tetromino(game_board_t* const, tetromino_t* const, double);
void petrity_tetromino(game_board_t* const, const tetromino_t*);
bool is_at_skyline(const tetromino_t*);

#endif /* __SIMULATE__H */
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

tetromino_status_t try_move_tetromino(const game_board_t* board, tetromino_t* const out_tetro, dir_t dir);
// tetromino_status_t move_tetromino_down(const game_board_t* board, tetromino_t* const out_tetro);
void petrity_tetromino(game_board_t* const out_board, const tetromino_t* tetro);
bool is_at_skyline(const tetromino_t* tetro);
void update_tetromino_ground_pos(const game_board_t* restrict board, tetromino_t* restrict const out_tetro);

// void try_rotate_tetromino_counterclockwise(game_board_t* const, tetromino_t* const);
// void try_rotate_tetromino_clockwise(game_board_t* const, tetromino_t* const);

#endif /* __SIMULATE__H */
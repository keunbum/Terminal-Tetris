#ifndef __UPDATE_TETROMINO_POS__H
#define __UPDATE_TETROMINO_POS__H

#include "tetris/tetris_play_manager.h"
#include "tetris_play_board.h"

typedef enum {
    TETROMINO_STATUS_INPLACE,
    TETROMINO_STATUS_MOVED,
    TETROMINO_STATUS_NULL,
    TETROMINO_STATUS_ONTHEGROUND,
} tetromino_status_t;

tetromino_status_t check_tetromino_next_status(const tetris_play_board_t* board, const tetromino_t* tetro, pos_t npos, dir_t ndir);
tetromino_status_t new_try_move_tetromino_r(const tetris_play_board_t* board, tetromino_t* const out_tetro, dir_t dir, game_time_t game_delta_time);

tetromino_status_t try_move_tetromino_byone_r(const tetris_play_board_t* board, tetromino_t* const out_tetro, dir_t dir);
tetromino_status_t try_rotate_tetromino_r(const tetris_play_board_t* board, tetromino_t* const out_tetro, int by);

void update_tetromino_ground_pos(const tetris_play_board_t* restrict board, tetromino_t* restrict const out_tetro);

tetromino_status_t harddrop_tetromino_r(tetromino_t* const out_tetro);

#endif /* __UPDATE_TETROMINO_POS__H */
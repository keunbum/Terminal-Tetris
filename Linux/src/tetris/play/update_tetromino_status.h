#ifndef __UPDATE_TETROMINO_POS__H
#define __UPDATE_TETROMINO_POS__H

#include "tetris/tetris_play_manager.h"
#include "tetris_play_board.h"

typedef enum {
    TETROMINO_STATUS_INPLACE,
    TETROMINO_STATUS_MOVED,
    TETROMINO_STATUS_ONTHEGROUND,
} tetromino_status_t;

tetromino_status_t new_check_tetromino_next_status(const tetris_play_board_t* board, const tetromino_t* tetro, pos_t npos, dir_t ndir);
tetromino_status_t new_try_move_tetromino_mainbody(const tetris_play_board_t* board, tetromino_t* const out_tetro, dir_t dir, game_time_t game_delta_time);
tetromino_status_t new_try_move_tetromino(const tetris_play_board_t* board, tetromino_t* const out_tetro, dir_t dir, game_time_t game_delta_time);

tetromino_status_t try_move_tetromino_byone(const tetris_play_board_t* board, tetromino_t* const out_tetro, dir_t dir);

tetromino_status_t try_rotate_tetromino(const tetris_play_board_t* board, tetromino_t* const out_tetro, int by);

void new_update_tetromino_ground_pos(const tetris_play_board_t* restrict board, tetromino_t* restrict const out_tetro);
void harddrop_tetromino(tetromino_t* const out_tetro);

#endif /* __UPDATE_TETROMINO_POS__H */
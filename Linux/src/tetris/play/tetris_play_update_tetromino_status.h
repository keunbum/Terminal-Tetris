#ifndef __TETRIS_PLAY_UPDATE_TETROMINO_STATUS__H
#define __TETRIS_PLAY_UPDATE_TETROMINO_STATUS__H

#include "tetris/object/board.h"

#define TETRIS_PLAY_SKY_LINE_POS_X (TETRIS_PLAY_BOARD_POS_X + 8)

// #define TETRIS_PLAY_TETROMINO_INIT_POS_X (-2)
// #define TETRIS_PLAY_TETROMINO_INIT_POS_Y (TETRIS_PLAY_BOARD_WIDTH / 2 - 1)

#define TETRIS_PLAY_TETROMINO_INIT_POS_X (TETRIS_PLAY_SKY_LINE_POS_X - 3)
#define TETRIS_PLAY_TETROMINO_INIT_POS_Y (TETRIS_PLAY_BOARD_POS_Y + TETRIS_PLAY_BOARD_WIDTH / 2 - 1)

#define TETRIS_PLAY_TETROMINO_POS_X_MIN (TETRIS_PLAY_TETROMINO_INIT_POS_X)
#define TETRIS_PLAY_TETROMINO_POS_X_MAX (TETRIS_PLAY_BOARD_HEIGHT - 1)
#define TETRIS_PLAY_TETROMINO_POS_Y_MIN (0)
#define TETRIS_PLAY_TETROMINO_POS_Y_MAX (TETRIS_PLAY_BOARD_WIDTH - 1)

#define TETRIS_PLAY_TETROMINO_UNIT_DISTANCE (1.0)
#define TETRIS_PLAY_TETROMINO_INIT_VELOCITY (TETRIS_PLAY_TETROMINO_UNIT_DISTANCE * 1.0)

typedef enum {
    TETROMINO_TRY_STATUS_INPLACE,
    TETROMINO_TRY_STATUS_MOVED,
    TETROMINO_TRY_STATUS_NULL,
    TETROMINO_TRY_STATUS_ONTHEGROUND,
} tetromino_try_status_t;

tetromino_try_status_t try_tetromino_next_status(board_t* const restrict out_board, const tetromino_t* restrict tetro, pos_t npos, dir_t ndir);
tetromino_try_status_t try_move_tetromino_deltatime_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, dir_t dir, game_time_t game_delta_time);
tetromino_try_status_t try_move_tetromino_byone_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, dir_t dir);
tetromino_try_status_t try_rotate_tetromino_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, int by);
tetromino_try_status_t harddrop_tetromino_r(tetromino_t* const out_tetro);

#endif /* __TETRIS_PLAY_UPDATE_TETROMINO_STATUS__H */
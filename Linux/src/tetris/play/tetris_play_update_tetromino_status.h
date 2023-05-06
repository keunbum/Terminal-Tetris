#ifndef __TETRIS_PLAY_UPDATE_TETROMINO_STATUS__H
#define __TETRIS_PLAY_UPDATE_TETROMINO_STATUS__H

#include "tetris/object/board.h"
#include "tetris_play_fps.h"

#define TETRIS_PLAY_TETROMINO_INIT_POS_X (TETRIS_PLAY_SKYLINE_POS_X)
#define TETRIS_PLAY_TETROMINO_INIT_POS_Y (TETRIS_PLAY_BOARD_POS_Y + TETRIS_PLAY_BOARD_WIDTH / 2 - 1)

#define TETRIS_PLAY_TETROMINO_POS_X_MIN (TETRIS_PLAY_TETROMINO_INIT_POS_X)
#define TETRIS_PLAY_TETROMINO_POS_X_MAX (TETRIS_PLAY_BOARD_POS_X + TETRIS_PLAY_BOARD_HEIGHT - 2)
#define TETRIS_PLAY_TETROMINO_POS_Y_MIN (TETRIS_PLAY_BOARD_POS_Y + 1)
#define TETRIS_PLAY_TETROMINO_POS_Y_MAX (TETRIS_PLAY_BOARD_POS_Y + TETRIS_PLAY_BOARD_WIDTH - 2)

#define TETRIS_PLAY_TETROMINO_UNIT_DISTANCE (1.0)
#define TETRIS_PLAY_UNIT_VELOCITY (0.04f)
#define TETRIS_PLAY_TETROMINO_INIT_VELOCITY (TETRIS_PLAY_TETROMINO_UNIT_DISTANCE * 1.0)

typedef enum {
    TETROMINO_STATUS_NULL,
    TETROMINO_STATUS_ONTHEWALL,
    TETROMINO_STATUS_MOVE,
    TETROMINO_STATUS_ROTATE,
    TETROMINO_STATUS_ONTHEGROUND,
} tetromino_status_t;

const wchar_t* get_tetromino_status_wstr(tetromino_status_t status);
bool is_ok_tetromino_next_status(const board_t* restrict board, const tetromino_t* restrict tetro, pos_int_t npos, dir_t ndir);
tetromino_status_t try_move_down_tetromino_deltatime_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, game_time_t delta_time);
tetromino_status_t try_move_tetromino_byone_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, dir_t dir);
tetromino_status_t try_rotate_tetromino_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, int by);
tetromino_status_t harddrop_tetromino_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro);

#endif /* __TETRIS_PLAY_UPDATE_TETROMINO_STATUS__H */
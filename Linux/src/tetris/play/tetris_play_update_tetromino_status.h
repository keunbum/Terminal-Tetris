#ifndef __TETRIS_PLAY_UPDATE_TETROMINO_STATUS__H
#define __TETRIS_PLAY_UPDATE_TETROMINO_STATUS__H

#include "tetris/object/board.h"

#define TETRIS_PLAY_TETROMINO_INIT_POS_X (TETRIS_PLAY_SKYLINE_POS_X - 3)
#define TETRIS_PLAY_TETROMINO_INIT_POS_Y (TETRIS_PLAY_BOARD_POS_Y + TETRIS_PLAY_BOARD_WIDTH / 2 - 1)

#define TETRIS_PLAY_TETROMINO_POS_X_MIN (TETRIS_PLAY_TETROMINO_INIT_POS_X)
#define TETRIS_PLAY_TETROMINO_POS_X_MAX (TETRIS_PLAY_BOARD_POS_X + TETRIS_PLAY_BOARD_HEIGHT - 2)
#define TETRIS_PLAY_TETROMINO_POS_Y_MIN (TETRIS_PLAY_BOARD_POS_Y + 1)
#define TETRIS_PLAY_TETROMINO_POS_Y_MAX (TETRIS_PLAY_BOARD_POS_Y + TETRIS_PLAY_BOARD_WIDTH - 2)

#define TETRIS_PLAY_TETROMINO_UNIT_DISTANCE (1.0)
// #define TETRIS_PLAY_TETROMINO_INIT_VELOCITY (TETRIS_PLAY_TETROMINO_UNIT_DISTANCE * 1.0)
#define TETRIS_PLAY_TETROMINO_INIT_VELOCITY (TETRIS_PLAY_TETROMINO_UNIT_DISTANCE * 1.0)

typedef enum {
    TETROMINO_TRY_STATUS_NULL,
    TETROMINO_TRY_STATUS_INPLACE,
    TETROMINO_TRY_STATUS_MOVE,
    TETROMINO_TRY_STATUS_ROTATE,
    TETROMINO_TRY_STATUS_ONTHEGROUND,
} tetromino_try_status_t;

static inline const wchar_t* get_tetomino_try_status_wstr(tetromino_try_status_t status)
{
    switch (status) {
    case TETROMINO_TRY_STATUS_NULL:
        return L"TETROMINO_TRY_STATUS_NULL";
    case TETROMINO_TRY_STATUS_INPLACE:
        return L"TETROMINO_TRY_STATUS_INPLACE";
    case TETROMINO_TRY_STATUS_MOVE:
        return L"TETROMINO_TRY_STATUS_MOVE";
    case TETROMINO_TRY_STATUS_ROTATE:
        return L"TETROMINO_TRY_STATUS_ROTATE";
    case TETROMINO_TRY_STATUS_ONTHEGROUND:
        return L"TETROMINO_TRY_STATUS_ONTHEGROUND";
    }
    my_assert(false);
}

tetromino_try_status_t try_tetromino_next_status(const board_t* restrict board, const tetromino_t* restrict tetro, pos_t npos, dir_t ndir);
tetromino_try_status_t try_move_tetromino_deltatime_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, dir_t dir, game_time_t delta_time);
tetromino_try_status_t try_move_tetromino_byone_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, dir_t dir);
tetromino_try_status_t try_rotate_tetromino_r(board_t* const restrict out_board, tetromino_t* const restrict out_tetro, int by);
tetromino_try_status_t harddrop_tetromino_r(board_t* const restrict out_board, tetromino_t* const out_tetro);

#endif /* __TETRIS_PLAY_UPDATE_TETROMINO_STATUS__H */
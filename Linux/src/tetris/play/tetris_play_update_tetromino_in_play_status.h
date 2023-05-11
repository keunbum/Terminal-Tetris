#ifndef __TETRIS_PLAY_UPDATE_TETROMINO_IN_PLAY_STATUS__H
#define __TETRIS_PLAY_UPDATE_TETROMINO_IN_PLAY_STATUS__H

#include "tetris/object/matrix.h"
#include "tetris_play_fps.h"

#define TETRIS_PLAY_TETROMINO_IN_PLAY_INIT_POS_X (TETRIS_PLAY_SKYLINE_POS_X - 2)
#define TETRIS_PLAY_TETROMINO_IN_PLAY_INIT_POS_Y (TETRIS_PLAY_MATRIX_IN_PLAY_POS_Y + 3)

#define TETRIS_PLAY_TETROMINO_IN_PLAY_POS_X_MIN (TETRIS_PLAY_TETROMINO_IN_PLAY_INIT_POS_X)
#define TETRIS_PLAY_TETROMINO_IN_PLAY_POS_X_MAX (TETRIS_PLAY_MATRIX_POS_X + TETRIS_PLAY_MATRIX_HEIGHT - 2)
#define TETRIS_PLAY_TETROMINO_IN_PLAY_POS_Y_MIN (TETRIS_PLAY_MATRIX_POS_Y + 1)
#define TETRIS_PLAY_TETROMINO_IN_PLAY_POS_Y_MAX (TETRIS_PLAY_MATRIX_POS_Y + TETRIS_PLAY_MATRIX_WIDTH - 2)

#define TETRIS_PLAY_TETROMINO_IN_PLAY_UNIT_DISTANCE (1.0)
#define TETRIS_PLAY_TETROMINO_IN_PLAY_UNIT_VELOCITY (0.04f)
#define TETRIS_PLAY_TETROMINO_IN_PLAY_INIT_VELOCITY (TETRIS_PLAY_TETROMINO_IN_PLAY_UNIT_DISTANCE * 1.0)

typedef enum {
    TETROMINO_IN_PLAY_STATUS_NULL,
    TETROMINO_IN_PLAY_STATUS_ONTHEWALL,
    TETROMINO_IN_PLAY_STATUS_MOVE,
    TETROMINO_IN_PLAY_STATUS_ROTATE,
    TETROMINO_IN_PLAY_STATUS_ONTHEGROUND,
} tetromino_in_play_status_t;

static inline pos_t get_tetromino_pos_wprint(pos_t pos)
{
    return create_pos(pos.x + __FLT_EPSILON__ - TETRIS_PLAY_MATRIX_IN_PLAY_HEIGHT, 2 * (pos.y + __FLT_EPSILON__));
}

static inline void update_tetromino_pos(tetromino_t* const out_tetro, pos_t pos)
{
    out_tetro->pos = pos;
    out_tetro->pos_wprint = get_tetromino_pos_wprint(out_tetro->pos);
}

const wchar_t* get_tetromino_in_play_status_wstr(tetromino_in_play_status_t status);
bool is_ok_tetromino_in_play_next_status(const matrix_t* restrict matrix, const tetromino_t* restrict tetro, pos_int_t npos, dir_t ndir);
tetromino_in_play_status_t try_move_down_tetromino_in_play_deltatime(matrix_t* const restrict out_board, tetromino_t* const restrict out_tetro, game_time_t delta_time);
tetromino_in_play_status_t try_move_tetromino_in_play_byone(matrix_t* const restrict out_board, tetromino_t* const restrict out_tetro, dir_t dir);
tetromino_in_play_status_t try_rotate_tetromino_in_play(matrix_t* const restrict out_board, tetromino_t* const restrict out_tetro, int by);
tetromino_in_play_status_t harddrop_tetromino_in_play(matrix_t* const restrict out_board, tetromino_t* const restrict out_tetro);

#endif /* __TETRIS_PLAY_UPDATE_TETROMINO_IN_PLAY_STATUS__H */
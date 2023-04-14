#ifndef __TETRIS_PLAY_UPDATE_TETROMINO_STATUS__H
#define __TETRIS_PLAY_UPDATE_TETROMINO_STATUS__H

// #include "tetris/tetris_play_manager.h"
#include "tetris/object/board.h"

#define TETRIS_PLAY_TETROMINO_INIT_POS_X (-2)
#define TETRIS_PLAY_TETROMINO_INIT_POS_Y (TETRIS_PLAY_BOARD_WIDTH / 2 - 1)

#define TETRIS_PLAY_TETROMINO_POS_X_MIN (TETRIS_PLAY_TETROMINO_INIT_POS_X)
#define TETRIS_PLAY_TETROMINO_POS_X_MAX (TETRIS_PLAY_BOARD_HEIGHT - 1)
#define TETRIS_PLAY_TETROMINO_POS_Y_MIN (0)
#define TETRIS_PLAY_TETROMINO_POS_Y_MAX (TETRIS_PLAY_BOARD_WIDTH - 1)

#define TETRIS_PLAY_TETROMINO_UNIT_DISTANCE (1.0)
// 1초마다 내려가는 칸 수.
#define TETRIS_PLAY_TETROMINO_INIT_VELOCITY (TETRIS_PLAY_TETROMINO_UNIT_DISTANCE * 1.0)

#define TETRIS_PLAY_TETROMINO_BLOCK_SILHOUETTE_WPRINT BLOCK_WPRINT_LIGHT_LARGE_SQUARE

typedef enum {
    TETROMINO_TRY_STATUS_INPLACE,
    TETROMINO_TRY_STATUS_MOVED,
    TETROMINO_TRY_STATUS_NULL,
    TETROMINO_TRY_STATUS_ONTHEGROUND,
} tetromino_try_status_t;

tetromino_try_status_t try_tetromino_next_status(const board_t* board, const tetromino_t* tetro, pos_t npos, dir_t ndir);

tetromino_try_status_t try_move_tetromino_deltatime_r(const board_t* board, tetromino_t* const out_tetro, dir_t dir, game_time_t game_delta_time);
tetromino_try_status_t try_move_tetromino_byone_r(const board_t* board, tetromino_t* const out_tetro, dir_t dir);
tetromino_try_status_t try_rotate_tetromino_r(const board_t* board, tetromino_t* const out_tetro, int by);
tetromino_try_status_t harddrop_tetromino_r(tetromino_t* const out_tetro);

// void update_tetromino_ground_pos(const board_t* restrict board, tetromino_t* restrict const out_tetro);

#endif /* __TETRIS_PLAY_UPDATE_TETROMINO_STATUS__H */
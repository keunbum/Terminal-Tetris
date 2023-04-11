#ifndef __SIMULATE__H
#define __SIMULATE__H

#include <stdbool.h>
#include <pthread.h>

#include "tetris/tetromino/tetromino.h"
#include "tetris_play_board.h"

typedef enum {
    TETROMINO_STATUS_INPLACE,
    TETROMINO_STATUS_MOVED,
    TETROMINO_STATUS_ONTHEGROUND,
} tetromino_status_t;

typedef pthread_spinlock_t update_lock_t;

extern update_lock_t g_update_lock;

#define init_tetris_play_update() func_check_error(pthread_spin_init, &g_update_lock, PTHREAD_PROCESS_PRIVATE)
#define tetris_play_update_lock() func_check_error(pthread_spin_lock, &g_update_lock)
#define tetris_play_update_unlock() func_check_error(pthread_spin_unlock, &g_update_lock)
#define cleanup_tetris_play_update() func_check_error(pthread_spin_destroy, &g_update_lock)

// tetromino_status_t try_move_tetromino(const game_board_t* board, tetromino_t* const out_tetro, dir_t dir);
// void petrity_tetromino(game_board_t* const out_board, const tetromino_t* tetro);
// bool is_at_skyline(const tetromino_t* tetro);
void update_tetromino_ground_pos(const game_board_t* restrict board, tetromino_t* restrict const out_tetro);

tetromino_status_t try_move_tetromino_r(const game_board_t* board, tetromino_t* const out_tetro, dir_t dir);
void petrity_tetromino_r(game_board_t* const out_board, const tetromino_t* tetro);
bool is_at_skyline_r(const tetromino_t* tetro);

// void try_rotate_tetromino_counterclockwise(game_board_t* const, tetromino_t* const);
// void try_rotate_tetromino_clockwise(game_board_t* const, tetromino_t* const);

#endif /* __SIMULATE__H */
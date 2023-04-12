#ifndef __SIMULATE__H
#define __SIMULATE__H

#include <pthread.h>
#include <stdbool.h>

#include "tetris/tetris_play_manager.h"
#include "update_tetromino_status.h"
#include "util.h"

typedef pthread_spinlock_t update_lock_t;

extern update_lock_t g_update_lock;

#define init_tetris_play_update() func_check_error(pthread_spin_init, &g_update_lock, PTHREAD_PROCESS_PRIVATE)
#define tetris_play_update_lock() func_check_error(pthread_spin_lock, &g_update_lock)
#define tetris_play_update_unlock() func_check_error(pthread_spin_unlock, &g_update_lock)
#define cleanup_tetris_play_update() func_check_error(pthread_spin_destroy, &g_update_lock)

void new_update_tetromino_ground_pos(const tetris_play_board_t* restrict board, tetromino_t* restrict const out_tetro);

void petrity_tetromino_r(tetris_play_board_t* const out_board, const tetromino_t* tetro);
bool is_at_skyline_r(const tetromino_t* tetro);
void update_gameworld(tetris_play_manager_t* const out_play_manager);

tetromino_status_t try_move_tetromino_byone_r(const tetris_play_board_t* board, tetromino_t* const out_tetro, dir_t dir);
tetromino_status_t try_rotate_tetromino_r(const tetris_play_board_t* board, tetromino_t* const out_tetro, int by);
void harddrop_tetromino_r(tetris_play_manager_t* const out_play_manager);

#endif /* __SIMULATE__H */
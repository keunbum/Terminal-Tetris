#ifndef __TETRIS_PLAY_BOARD__H
#define __TETRIS_PLAY_BOARD__H

#include <wchar.h>
#include <pthread.h>

#include "tetris/scene/tetris_play_screen.h"
#include "tetris/tetromino/tetromino.h"

#define TETRIS_PLAY_BOARD_HEIGHT (20)
#define TETRIS_PLAY_BOARD_WIDTH (10)

#define TETRIS_PLAY_BOARD_HEIGHT_WPRINT (TETRIS_PLAY_BOARD_HEIGHT)
#define TETRIS_PLAY_BOARD_WIDTH_WPRINT (2 * TETRIS_PLAY_BOARD_WIDTH)

#define TETRIS_PLAY_BOARD_GRID_ELEMENT_DEFAULT (0)

#define TETRIS_PLAY_TETROMINO_INIT_POS_X (-2)
#define TETRIS_PLAY_TETROMINO_INIT_POS_Y (TETRIS_PLAY_BOARD_WIDTH / 2 - 1)

#define TETRIS_PLAY_TETROMINO_POS_X_MIN (TETRIS_PLAY_TETROMINO_INIT_POS_X)
#define TETRIS_PLAY_TETROMINO_POS_X_MAX (TETRIS_PLAY_BOARD_HEIGHT - 1)
#define TETRIS_PLAY_TETROMINO_POS_Y_MIN (0)
#define TETRIS_PLAY_TETROMINO_POS_Y_MAX (TETRIS_PLAY_BOARD_WIDTH - 1)

#define TETRIS_PLAY_TETROMINO_UNIT_DISTANCE (1.0)
#define TETRIS_PLAY_TETROMINO_INIT_VELOCITY (TETRIS_PLAY_TETROMINO_UNIT_DISTANCE) * 1

// 1초마다 내려가는 칸 수.
#define NEW_TETRIS_PLAY_TETROMINO_INIT_VELOCITY (TETRIS_PLAY_TETROMINO_UNIT_DISTANCE * 3.0)

#define TETRIS_PLAY_BOARD_START_POS_X_WPRINT \
    (TETRIS_PLAY_SINGLE_SCREEN_START_POS_X_WPRINT + (TETRIS_PLAY_SINGLE_SCREEN_HEIGHT_WPRINT - TETRIS_PLAY_BOARD_HEIGHT_WPRINT) / 2 + 4)

#define TETRIS_PLAY_BOARD_START_POS_Y_WPRINT \
    (TETRIS_PLAY_SINGLE_SCREEN_START_POS_Y_WPRINT + (TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT - TETRIS_PLAY_BOARD_WIDTH_WPRINT) / 2 + 0)

/* may be changed. */
typedef tetromino_id_t tetris_play_board_grid_element_t;
typedef pthread_spinlock_t tetris_play_board_lock_t;

extern tetris_play_board_lock_t g_tetris_play_board_lock;

typedef struct {
    int height;
    int width;
    int height_wprint;
    int width_wprint;
    tetris_play_board_grid_element_t grid[TETRIS_PLAY_BOARD_HEIGHT][TETRIS_PLAY_BOARD_WIDTH];
} tetris_play_board_t;

#define init_tetris_play_board_lock() func_check_error(pthread_spin_init, &g_tetris_play_board_lock, PTHREAD_PROCESS_PRIVATE)
#define tetris_play_board_lock() func_check_error(pthread_spin_lock, &g_tetris_play_board_lock)
#define tetris_play_board_unlock() func_check_error(pthread_spin_unlock, &g_tetris_play_board_lock)
#define cleanup_tetris_play_board_lock() func_check_error(pthread_spin_destroy, &g_tetris_play_board_lock)

void init_game_board(tetris_play_board_t* const);

#endif /* __TETRIS_PLAY_BOARD__H */
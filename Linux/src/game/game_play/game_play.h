#ifndef __GAME_PLAY__H
#define __GAME_PLAY__H

#include "game/game_play/ui/game_play_grid_matrix.h"
#include "game/game_play/ui/game_play_screen.h"

#define GAME_PLAY_CMD_EXIT_GAME (0)
#define GAME_PLAY_CMD_ERROR (-1)

#define GAME_PLAY_STATUS_GAME_OVER (2)

#define GAME_PLAY_TIME_LIMIT (100)

#define GAME_PLAY_TIMER_INIT_EXPIRE_SEC (1)
#define GAME_PLAY_TIMER_INIT_EXPIRE_NSEC (0)

#define GAME_PLAY_TIMER_INTERVAL_SEC (1)
#define GAME_PLAY_TIMER_INTERVAL_NSEC (0)

#define GAME_PLAY_TIMER_POS_X (GAME_PLAY_SCREEN_START_POS_X + 2)
#define GAME_PLAY_TIMER_POS_Y (GAME_PLAY_SCREEN_START_POS_Y + GAME_PLAY_SCREEN_WIDTH + 2)

#define GAME_PLAY_TIMEINTERVAL_BEFORESTART_SEC (3)

#define GAME_PLAY_INIT_TETROMINO_POS_X (GAME_PLAY_GRID_MATRIX_START_POS_X)
#define GAME_PLAY_INIT_TETROMINO_POS_Y (GAME_PLAY_GRID_MATRIX_START_POS_Y + GAME_PLAY_GRID_MATRIX_WIDTH / 2)
#define GAME_PLAY_INIT_TETROMINO_VELOCITY (1)

// #define GAME_PLAY_TETROMINO_UNIT_VELOCITY (1)

typedef void* (*game_play_func_t)(void* arg);

typedef struct {
    game_play_func_t func;
    void* arg;
} game_play_module_t;

#endif /* __GAME_PLAY__H */

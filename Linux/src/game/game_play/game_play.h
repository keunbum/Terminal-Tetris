#ifndef __GAME_PLAY__H
#define __GAME_PLAY__H

#include <stdbool.h>
#include <pthread.h>

#include "game/game_play/physics/game_play_board_frame.h"
#include "game/game_play/ui/game_play_screen.h"

#define GAME_PLAY_CMD_EXIT_GAME (0)
#define GAME_PLAY_CMD_ERROR (-1)
#define GAME_PLAY_CMD_REGAME (1)

#define GAME_PLAY_STATUS_GAME_OVER (2)

//#define GAME_PLAY_TIME_LIMIT (100)

#define GAME_PLAY_TIMER_POS_X_WPRINT (GAME_PLAY_SINGLE_SCREEN_START_POS_X_WPRINT + 2)
#define GAME_PLAY_TIMER_POS_Y_WPRINT (GAME_PLAY_SINGLE_SCREEN_START_POS_Y_WPRINT + GAME_PLAY_SINGLE_SCREEN_WIDTH_WPRINT + 2)

#define GAME_PLAY_TIMEINTERVAL_BEFORESTART_SEC (3)

#define GAME_PLAY_TETROMINO_INIT_POS_X (-5)
#define GAME_PLAY_TETROMINO_INIT_POS_Y (GAME_PLAY_BOARD_WIDTH / 2)

#define GAME_PLAY_TETROMINO_POS_X_MIN (GAME_PLAY_TETROMINO_INIT_POS_X)
#define GAME_PLAY_TETROMINO_POS_X_MAX (GAME_PLAY_BOARD_HEIGHT - 1)
#define GAME_PLAY_TETROMINO_POS_Y_MIN (0)
#define GAME_PLAY_TETROMINO_POS_Y_MAX (GAME_PLAY_BOARD_WIDTH - 1)

#define GAME_PLAY_TETROMINO_UNIT_VELOCITY (1)
#define GAME_PLAY_TETROMINO_INIT_VELOCITY GAME_PLAY_TETROMINO_UNIT_VELOCITY

typedef void* (*game_play_func_t)(void* arg);

typedef struct {
    pthread_t pthread_id;
    game_play_func_t main_func;
    void* main_func_arg;
    bool is_detached;
    void* retval;
} game_play_module_t;

extern const struct timespec G_GAME_PLAY_TIMER_INIT_EXPIRE;
extern const struct timespec G_GAME_PLAY_TIMER_INTERVAL;

#endif /* __GAME_PLAY__H */

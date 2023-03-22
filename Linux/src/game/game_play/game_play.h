#ifndef __GAME_PLAY__H
#define __GAME_PLAY__H

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

typedef void* (*game_play_module_t)(void* arg);

#endif /* __GAME_PLAY__H */
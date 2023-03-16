#ifndef __GAME_MANAGER__H
#define __GAME_MANAGER__H

#include "game/game_play/game_play_screen.h"

#define EXIT_GAME_OVER (2)

#define GAME_PLAY_TIME_LIMIT (2)

#define GAME_PLAY_UNIT_SEC (1)

#define GAME_CONSOLE_STDOUT_POS_X (GAME_PLAY_SCREEN_START_POS_X + GAME_PLAY_SCREEN_HEIGHT + 1)
#define GAME_CONSOLE_STDOUT_POS_Y (0)

#define GAME_CONSOLE_STDERR_POS_X (GAME_PLAY_SCREEN_START_POS_X)
#define GAME_CONSOLE_STDERR_POS_Y (GAME_PLAY_SCREEN_START_POS_Y + GAME_PLAY_SCREEN_WIDTH + 5)

typedef void* (*module_t)(void *);

void run_title_menu(void);

#endif /* __GAME_MANAGER__H */
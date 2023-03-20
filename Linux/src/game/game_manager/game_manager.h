#ifndef __GAME_MANAGER__H
#define __GAME_MANAGER__H

#include "game/game_play/ui/game_play_screen.h"

#define GAME_CONSOLE_STDOUT_POS_X (GAME_PLAY_SCREEN_START_POS_X + GAME_PLAY_SCREEN_HEIGHT + 1)
#define GAME_CONSOLE_STDOUT_POS_Y (0)

#define GAME_CONSOLE_STDERR_POS_X (GAME_PLAY_SCREEN_START_POS_X)
#define GAME_CONSOLE_STDERR_POS_Y (GAME_PLAY_SCREEN_START_POS_Y + GAME_PLAY_SCREEN_WIDTH + 5)

// typedef void* (*module_t)(void *);

void run_game_manager(void);

#endif /* __GAME_MANAGER__H */
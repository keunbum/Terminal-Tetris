#ifndef __GAME_PLAY_TIMER
#define __GAME_PLAY_TIMER

#include "game/game_play/game_play_screen.h"

#define GAME_PLAY_UNIT_SEC (1)

#define GAME_PLAY_TIMER_POS_X (GAME_PLAY_SCREEN_START_POS_X + 2)
#define GAME_PLAY_TIMER_POS_Y (GAME_PLAY_SCREEN_START_POS_Y + GAME_PLAY_SCREEN_WIDTH + 2)

void* run_game_play_timer(void *);

#endif /* __GAME_PLAY_TIMER */
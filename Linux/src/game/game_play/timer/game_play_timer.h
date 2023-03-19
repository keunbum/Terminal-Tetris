#ifndef __GAME_PLAY_TIMER__H
#define __GAME_PLAY_TIMER__H

#include "game/game_play/timer/game_play_timer.h"

#define GAME_PLAY_UNIT_SEC (1)

#define GAME_PLAY_TIMER_POS_X (GAME_PLAY_SCREEN_START_POS_X + 2)
#define GAME_PLAY_TIMER_POS_Y (GAME_PLAY_SCREEN_START_POS_Y + GAME_PLAY_SCREEN_WIDTH + 2)

void draw_game_play_timer_at_with(int, int, int);
void* main_func_for_game_play_timer(void *);

#endif /* __GAME_PLAY_TIMER__H */
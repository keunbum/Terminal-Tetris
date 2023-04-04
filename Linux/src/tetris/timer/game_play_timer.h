#ifndef __GAME_PLAY_TIMER__H
#define __GAME_PLAY_TIMER__H

#define GAME_PLAY_TIMER_IT_VALUE_SEC (1)
#define GAME_PLAY_TIMER_IT_VALUE_NSEC (0)
#define GAME_PLAY_TIMER_IT_INTERVAL_SEC (1)
#define GAME_PLAY_TIMER_IT_INTERVAL_NSEC (0)

void draw_game_play_timer_at_with_r(int, int, int);
void* main_func_game_play_timer(void*);

#endif /* __GAME_PLAY_TIMER__H */
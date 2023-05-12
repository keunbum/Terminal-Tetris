#ifndef __TETRIS_PLAY_TIMER__H
#define __TETRIS_PLAY_TIMER__H

#include "game_play_timer.h"

#define TETRIS_PLAY_TIMER_IT_VALUE_SEC (1)
#define TETRIS_PLAY_TIMER_IT_VALUE_NSEC (0)
#define TETRIS_PLAY_TIMER_IT_INTERVAL_SEC (1)
#define TETRIS_PLAY_TIMER_IT_INTERVAL_NSEC (0)

typedef struct {
    int sec;
    frame_t clock_frame;
} tetris_play_timer_info_t;

static inline void init_tetris_play_timer_info(tetris_play_timer_info_t* const out_info, int init_sec, frame_t init_frame)
{
    out_info->sec = init_sec;
    init_frame_with(&out_info->clock_frame, &init_frame);
}

static inline void cleanup_tetris_play_timer_info(tetris_play_timer_info_t* const out_info)
{
    cleanup_frame(&out_info->clock_frame);
}

typedef struct {
    tetris_play_timer_info_t timer_info;
    game_play_timer_t game_play_timer;
} tetris_play_timer_t;

void init_tetris_play_timer(tetris_play_timer_t* const out_timer, pos_int_t timer_pos_wprint, int timersig);
void cleanup_tetris_play_timer(tetris_play_timer_t* const out_timer);
void* run_tetris_play_timer(void*);

#endif /* __TETRIS_PLAY_TIMER__H */
#include <stdio.h>
#include <wchar.h>

#include "debug.h"
#include "draw/draw_tool.h"
#include "tetris_play_timer.h"

#define TIMER_FRAME_CORNER_TOP_LEFT (L'┌')
#define TIMER_FRAME_CORNER_TOP_RIGHT (L'┐')
#define TIMER_FRAME_CORNER_BOT_LEFT (L'└')
#define TIMER_FRAME_CORNER_BOT_RIGHT (L'┘')

#define TIMER_FRAME_UNIT_HOR (L'─')
#define TIMER_FRAME_UNIT_VER (L'│')
#define TIMER_FRAME_UNIT_SPACE (L' ')

#define TIMER_FRAME_WIDTH (14)

static void decode_sec_to_hhmmss(int sec, int* const out_hh, int* const out_mm, int* const out_ss)
{
    *out_hh = sec / 3600;
    *out_mm = (sec % 3600) / 60;
    *out_ss = sec % 60;
}

static void draw_sec_in_hhmmss_at(int sec, pos_int_t clock_pos_wprint)
{
    int hh, mm, ss;
    decode_sec_to_hhmmss(sec, &hh, &mm, &ss);
    wprintf_at_r(clock_pos_wprint.x, clock_pos_wprint.y, L"%02d:%02d:%02d\n", hh, mm, ss);
    // wprintf_at_r(clock_pos_x_wprint, clock_pos_y_wprint, L"%02d:%02d:%02d", hh, mm, ss);
}

void tetris_play_timer_before_routine(void* arg)
{
    tetris_play_timer_info_t* const timer_info = (tetris_play_timer_info_t*)arg;
    timer_info->sec = 0;
    wdraw_frame(&timer_info->clock_frame, 5);
    pos_int_t clock_pos_wprint = { timer_info->clock_frame.pos_wprint.x + 1, timer_info->clock_frame.pos_wprint.y + 3 };
    draw_sec_in_hhmmss_at(timer_info->sec, clock_pos_wprint);
}

static void draw_tetris_play_timer(void* arg)
{
    tetris_play_timer_info_t* const timer_info = (tetris_play_timer_info_t*)arg;
    pos_int_t clock_pos_wprint = { timer_info->clock_frame.pos_wprint.x + 1, timer_info->clock_frame.pos_wprint.y + 3 };
    draw_sec_in_hhmmss_at(++timer_info->sec, clock_pos_wprint);
}

void init_tetris_play_timer(tetris_play_timer_t* const out_timer, pos_int_t frame_pos_wprint, int timersig)
{
    frame_t clock_frame;
    init_frame(&clock_frame,
        3, TIMER_FRAME_WIDTH,
        frame_pos_wprint,
        L"Time",
        TIMER_FRAME_UNIT_HOR,
        TIMER_FRAME_UNIT_VER,
        TIMER_FRAME_CORNER_TOP_LEFT,
        TIMER_FRAME_CORNER_TOP_RIGHT,
        TIMER_FRAME_CORNER_BOT_LEFT,
        TIMER_FRAME_CORNER_BOT_RIGHT);
    init_tetris_play_timer_info(&out_timer->timer_info, 0, clock_frame);
    init_game_play_timer(
        &out_timer->game_play_timer,
        REALTIME_TIMER_CLOCK_ID,
        timersig,
        (struct itimerspec) { { TETRIS_PLAY_TIMER_IT_INTERVAL_SEC, TETRIS_PLAY_TIMER_IT_INTERVAL_NSEC }, { TETRIS_PLAY_TIMER_IT_VALUE_SEC, TETRIS_PLAY_TIMER_IT_VALUE_NSEC } },
        (game_play_timer_module_t) { tetris_play_timer_before_routine, (void*)&out_timer->timer_info },
        (game_play_timer_module_t) { draw_tetris_play_timer, (void*)&out_timer->timer_info });
}

void cleanup_tetris_play_timer(tetris_play_timer_t* const out_timer)
{
    cleanup_game_play_timer(&out_timer->game_play_timer);
    cleanup_tetris_play_timer_info(&out_timer->timer_info);
}

void* run_tetris_play_timer(void* arg)
{
    tetris_play_timer_t* const tetris_play_timer = (tetris_play_timer_t*)arg;
    return run_game_play_timer(&tetris_play_timer->game_play_timer);
}

#include <stdio.h>

#include "debug.h"
#include "draw/draw_tool.h"
#include "timer_drawer.h"

static void decode_sec_to_hhmmss(int sec, int* const out_hh, int* const out_mm, int* const out_ss)
{
    *out_hh = sec / 3600;
    *out_mm = (sec % 3600) / 60;
    *out_ss = sec % 60;
}

static void draw_sec_in_hhmmss_at_r(int sec, int pos_x, int pos_y)
{
    int hh, mm, ss;
    decode_sec_to_hhmmss(sec, &hh, &mm, &ss);
    // wprintf_at_r(pos_x, pos_y, L"%02d:%02d:%02d\n", hh, mm, ss);
    wprintf_at_r(pos_x, pos_y, L"%02d:%02d:%02d", hh, mm, ss);
}

void draw_game_play_timer_at_with_r(int x, int y, int sec)
{
    draw_sec_in_hhmmss_at_r(sec, x, y);
}

void* mainfunc_game_play_timer(void* arg)
{
    return run_timer_drawer_with(arg);
}

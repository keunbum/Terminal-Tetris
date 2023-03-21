#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "debug/debug.h"
#include "draw_tool/cursor.h"
#include "game/game_play/timer/game_play_timer.h"
#include "game/game_play/timer/realtime_timer_drawer.h"

static void decode_sec_to_hhmmss(int sec, int* const out_hh, int* const out_mm, int* const out_ss)
{
    debug();

    my_assert(out_hh != NULL);
    my_assert(out_mm != NULL);
    my_assert(out_ss != NULL);

    *out_hh = sec / 3600;
    *out_mm = (sec % 3600) / 60;
    *out_ss = sec % 60;
}

/* It might be better to print it out in the form of a digital clock.. */
/* ref: https://www.acmicpc.net/problem/1020 */
static void draw_sec_in_hhmmss_at(int sec, int pos_x, int pos_y)
{
    debug();

    int hh, mm, ss;
    decode_sec_to_hhmmss(sec, &hh, &mm, &ss);
    wprintf_at(pos_x, pos_y, L"%02d:%02d:%02d\n", hh, mm, ss);
}

void draw_game_play_timer_at_with(int x, int y, int sec)
{
    debug();

    draw_sec_in_hhmmss_at(sec, x, y);
}

void* main_func_for_game_play_timer(void* arg)
{
    return new_run_realtime_timer_drawer_with(arg);
//    return run_realtime_timer_drawer_with(arg);
}

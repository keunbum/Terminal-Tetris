#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "debug.h"
#include "draw/cursor.h"
#include "game_play_timer.h"
#include "timer_drawer.h"

/* It will be printed a bit prettier. */

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

static void draw_sec_in_hhmmss_at_r(int sec, int pos_x, int pos_y)
{
    debug();

    int hh, mm, ss;
    decode_sec_to_hhmmss(sec, &hh, &mm, &ss);
    wprintf_at_r(pos_x, pos_y, L"%02d:%02d:%02d\n", hh, mm, ss);
}

void draw_game_play_timer_at_with_r(int x, int y, int sec)
{
    debug();

    draw_sec_in_hhmmss_at_r(sec, x, y);
}

void* main_func_game_play_timer(void* arg)
{
    debug();
    return run_timer_drawer_with(arg);
}

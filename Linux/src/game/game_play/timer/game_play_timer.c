#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "debug/debug.h"
#include "game/draw_tool/cursor.h"
#include "game/game_play/timer/game_play_timer.h"
#include "game/game_play/timer/realtime_timer.h"

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

static void draw_sec_in_hhmmss(int sec)
{
    debug();

    int hh, mm, ss;
    decode_sec_to_hhmmss(sec, &hh, &mm, &ss);
    wprintf(L"Time: %02d:%02d:%02d\n", hh, mm, ss);
}

void draw_game_play_timer_at_with(int sx, int sy, int sec)
{
    debug();

    wgotoxy(sx, sy);
    draw_sec_in_hhmmss(sec);
}

void* main_func_for_game_play_timer(void* arg)
{
    return run_realtime_timer_with(arg);
}

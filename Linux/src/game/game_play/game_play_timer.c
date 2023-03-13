#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "debug/debug.h"
#include "game/draw_manager/draw_manager.h"
#include "game/draw_manager/cursor.h"
#include "game/game_manager/game_manager.h"
#include "game/game_play/game_play_timer.h"
#include "util/util.h"

void run_game_play_timer(const void* arg)
{
    debug();
    int time_limit = *(int *) arg;
    forn(i, time_limit)
    {
        draw_game_play_timer_at_with(GAME_PLAY_TIMER_POS_X, GAME_PLAY_TIMER_POS_Y, i + 1);
        sleep(GAME_PLAY_UNIT_SEC);
    }
    exit(EXIT_GAME_OVER);
}
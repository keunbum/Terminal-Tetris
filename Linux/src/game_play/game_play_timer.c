#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "draw/draw_manager.h"
#include "draw/cursor.h"
#include "game_manager/game_manager.h"
#include "util/util.h"
#include "game_play/game_play_timer.h"

void run_game_play_timer(const void* arg)
{
    int time_limit = *(int *) arg;
    forn(i, time_limit)
    {
        draw_game_play_timer_at(GAME_PLAY_TIMER_POS_X, GAME_PLAY_TIMER_POS_Y, i + 1);
        sleep(GAME_PLAY_UNIT_SEC);
    }
    exit(EXIT_GAME_OVER);
}
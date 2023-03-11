#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "logic/game_manager.h"
#include "debug/local_debug.h"
#include "ui/hud.h"
#include "draw/cursor.h"
#include "util/util.h"

void run_draw_time_at()
{
    int sx = SCREEN_START_X + 2;
    int sy = SCREEN_START_Y + 2;
    forn(i, MAX_PLAY_TIME)
    {
        draw_time_at(sx, sy, i + 1);
        sleep(UNIT_SEC);
    }
    exit(EXIT_GAME_OVER);
}
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "game_manager.h"
#include "local_debug.h"
#include "hud.h"
#include "cursor.h"
#include "util.h"

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
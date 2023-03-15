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

/* Actually, it's not a proper implementation,
   because the draw_game_play_timer_at_with function is not executed in parallel.
   Perhaps you should use a timer-related system call.. Search a lot.
   ref: https://man7.org/linux/man-pages/man2/timer_create.2.html
        https://man7.org/linux/man-pages/man2/alarm.2.html 
 */
void run_game_play_timer(const void* arg)
{
    debug();
    
    int time_limit = *(int *) arg;
    forn(i, time_limit)
    {
        draw_game_play_timer_at_with(GAME_PLAY_TIMER_POS_X, GAME_PLAY_TIMER_POS_Y, i + 1);
        sleep(GAME_PLAY_UNIT_SEC);
    }
    /* If it was threaded, it wouldn't be a proper exit statement. */
    exit(EXIT_GAME_OVER);
}
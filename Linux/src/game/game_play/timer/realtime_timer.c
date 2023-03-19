#include <stddef.h>
#include <unistd.h>

#include "debug/debug.h"
#include "game/game_play/timer/realtime_timer.h"
#include "util/util.h"

/* Actually, it's not a proper implementation,
   because the 'run_realtime_timer_with' function is not executed in parallel.
   Perhaps you should use a timer-related system call.. Search a lot.
   ref: https://man7.org/linux/man-pages/man2/timer_create.2.html
        https://man7.org/linux/man-pages/man2/alarm.2.html 
        https://man7.org/linux/man-pages/man3/clock_gettime.3.html
 */
void* run_realtime_timer_with(void* arg)
{
    debug();

    const realtime_timer_data_t* timer_data_ptr = (realtime_timer_data_t *) arg;
    const draw_module_t* draw_module_ptr = &timer_data_ptr->draw_module;

    forn (i, timer_data_ptr->time_limit) {
        draw_module_ptr->draw_func(draw_module_ptr->pos_x, draw_module_ptr->pos_y, i + 1);
        sleep(draw_module_ptr->unit_sec);
    }
    /* If it was threaded, it wouldn't be a proper exit statement. */
    // exit(EXIT_GAME_OVER);
    return NULL;
}

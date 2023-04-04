#include "realtime_timer.h"

void set_realtime_timer(realtime_timer_t* const out_timer, bool is_on)
{
    out_timer->is_running = ATOMIC_VAR_INIT(is_on);
}

bool is_realtimer_timer_running(const realtime_timer_t* timer)
{
    return atomic_load(&timer->is_running);
}
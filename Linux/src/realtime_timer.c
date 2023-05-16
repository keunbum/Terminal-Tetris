#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "debug.h"
#include "error_handling.h"
#include "realtime_timer.h"

void init_realtime_timer(realtime_timer_t* const out_realtime_timer, clockid_t clockid, int timersig, struct itimerspec its)
{
    out_realtime_timer->clockid = clockid;
    out_realtime_timer->timersig = timersig;
    out_realtime_timer->its = its;
}

void cleanup_realtime_timer(realtime_timer_t* const out_realtime_timer)
{
    (void)out_realtime_timer;
}

void register_realtime_timer(realtime_timer_t* const out_realtime_timer)
{
    my_assert(out_realtime_timer->timersig == TETRIS_PLAY_TIMER_SIG);

    /* Set sigset */
    sigemptyset(&out_realtime_timer->sigset);
    sigaddset(&out_realtime_timer->sigset, out_realtime_timer->timersig);

    sigevent_t sev = {
        .sigev_notify = SIGEV_SIGNAL,
        .sigev_signo = out_realtime_timer->timersig,
        .sigev_value.sival_int = 0,
        ._sigev_un._sigev_thread._function = NULL,
    };

    /* Create timer */
    if (timer_create(out_realtime_timer->clockid, &sev, &out_realtime_timer->timerid) == -1) {
        handle_error("timer_create() error");
    }
}

void remove_realtime_timer(realtime_timer_t* const out_realtime_timer)
{
    my_assert(out_realtime_timer != NULL);

    if (timer_delete(out_realtime_timer->timerid) == -1) {
        handle_error("timer_delete() error");
    }
}

void start_realtime_timer(realtime_timer_t* const out_realtime_timer)
{
    if (timer_settime(out_realtime_timer->timerid, 0, &out_realtime_timer->its, NULL) == -1) {
        handle_error("timer_settime() error");
    }
}
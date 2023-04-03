#ifndef __REALTIME_TIMER__H
#define __REALTIME_TIMER__H

#include <signal.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <time.h>

#define REALTIME_TIMER_CLOCK_ID CLOCK_REALTIME

typedef int timer_sig_t;

typedef struct realtime_timer realtime_timer_t;
struct realtime_timer {
    timer_t timerid;
    clockid_t clockid;
    sigset_t sigset;
    timer_sig_t timer_sig;
    atomic_bool is_running;
    struct itimerspec its;
};

void set_realtime_timer(realtime_timer_t* const, bool);
bool is_realtimer_timer_running(const realtime_timer_t*);

#endif /* __REALTIME_TIMER__H */
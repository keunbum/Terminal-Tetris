#ifndef __REALTIME_TIMER__H
#define __REALTIME_TIMER__H

#include <signal.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <time.h>

#define REALTIME_TIMER_CLOCK_ID CLOCK_REALTIME
#define REALTIME_TIMER_SIG SIGRTMIN

// typedef struct realtime_timer realtime_timer_t;
// typedef void* (*timer_main_logic_t)(const realtime_timer_t*);

typedef struct {
    timer_t timerid;
    clockid_t clockid;
    sigset_t sigset;
    int timersig;
    atomic_bool is_running;
    struct itimerspec its;
    // timer_main_logic_t logic;
    // void* logic_arg;
} realtime_timer_t;

static inline void set_realtime_timer(realtime_timer_t* const out_timer, bool is_on)
{
    out_timer->is_running = ATOMIC_VAR_INIT(is_on);
}

static inline bool is_realtime_timer_running(const realtime_timer_t* timer)
{
    return atomic_load(&timer->is_running);
}

#endif /* __REALTIME_TIMER__H */
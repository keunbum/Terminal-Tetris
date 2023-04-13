#ifndef __REALTIME_TIMER__H
#define __REALTIME_TIMER__H

#include <signal.h>
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
    struct itimerspec its;
    // timer_main_logic_t logic;
    // void* logic_arg;
} realtime_timer_t;

#endif /* __REALTIME_TIMER__H */
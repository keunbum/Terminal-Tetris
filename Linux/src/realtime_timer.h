#ifndef __REALTIME_TIMER__H
#define __REALTIME_TIMER__H

#include <signal.h>
#include <time.h>

#define REALTIME_TIMER_CLOCK_ID CLOCK_REALTIME

typedef struct {
    timer_t timerid;
    clockid_t clockid;
    sigset_t sigset;
    int timersig;
    struct itimerspec its;
} realtime_timer_t;

void init_realtime_timer(realtime_timer_t* const out_realtime_timer, clockid_t clockid, int timersig, struct itimerspec its);
void cleanup_realtime_timer(realtime_timer_t* const out_realtime_timer);
void register_realtime_timer(realtime_timer_t* const out_realtime_timer);
void remove_realtime_timer(realtime_timer_t* const out_realtime_timer);
void start_realtime_timer(realtime_timer_t* const out_realtime_timer);

#endif /* __REALTIME_TIMER__H */
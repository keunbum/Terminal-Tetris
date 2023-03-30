#ifndef __REALTIME_TIMER_DRAWER__H
#define __REALTIME_TIMER_DRAWER__H

#include <stdatomic.h>
#include <time.h>

#define REALTIME_TIMER_SIG SIGRTMIN

typedef void (*draw_func_t)(int, int, int);

typedef struct {
    int pos_x;
    int pos_y;
    struct itimerspec its;
    draw_func_t draw_func;
} draw_module_t;

typedef struct {
    int time_limit;
    draw_module_t draw_module;
} realtime_timer_data_t;

extern atomic_bool g_realtime_timer_running;

void* run_realtime_timer_drawer_with(void* arg);

#endif /* __REALTIME_TIMER_DRAWER__H */
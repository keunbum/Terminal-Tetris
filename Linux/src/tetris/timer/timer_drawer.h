#ifndef __TIMER_DRAWER__H
#define __TIMER_DRAWER__H

#include <stdbool.h>

#include "realtime_timer.h"

typedef void (*draw_func_t)(int, int, int);

typedef struct {
    int pos_x_wprint;
    int pos_y_wprint;
    draw_func_t draw_func;
} draw_module_t;

typedef struct {
    realtime_timer_t timer;
    draw_module_t draw_module;
} timer_drawer_t;

void init_timer_drawer(timer_drawer_t* const out_timer_drawer, int timersig);
void* run_timer_drawer_with(void* arg);

#endif /* __TIMER_DRAWER__H */
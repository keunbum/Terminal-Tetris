#ifndef __REALTIME_TIMER__H
#define __REALTIME_TIMER__H

typedef void (*draw_func_t)(int, int, int);

typedef struct {
    int pos_x;
    int pos_y;
    int unit_sec;
    draw_func_t draw_func;
} draw_module_t;

typedef struct {
    int time_limit;
    draw_module_t draw_module;
} realtime_timer_data_t;

void* run_realtime_timer_with(void* arg);

#endif /* __REALTIME_TIMER__H */
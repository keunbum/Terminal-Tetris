#include <signal.h>

#include "debug.h"
#include "draw/draw_tool.h"
#include "pthread_macro.h"
#include "signal_macro.h"
#include "timer_drawer.h"
#include "timer_frame.h"

static void wdraw_timer_frame_at(int pos_x_wprint, int pos_y_wprint)
{
    // debug();

    static wchar_t s_top_line[TIMER_FRAME_WIDTH + 1];
    static wchar_t s_mid_line[TIMER_FRAME_WIDTH + 1];
    static wchar_t s_bot_line[TIMER_FRAME_WIDTH + 1];
    static wchar_t* s_strs[] = { s_top_line, s_mid_line, s_bot_line };
    static const int S_STR_NUM = 3;

    wset_row_line(s_top_line, TIMER_FRAME_WIDTH, TIMER_FRAME_CORNER_TOP_LEFT, TIMER_FRAME_UNIT_HOR, TIMER_FRAME_CORNER_TOP_RIGHT);
    wset_row_line(s_mid_line, TIMER_FRAME_WIDTH, TIMER_FRAME_UNIT_VER, TIMER_FRAME_UNIT_SPACE, TIMER_FRAME_UNIT_VER);
    wset_row_line(s_bot_line, TIMER_FRAME_WIDTH, TIMER_FRAME_CORNER_BOT_LEFT, TIMER_FRAME_UNIT_HOR, TIMER_FRAME_CORNER_BOT_RIGHT);

    wdraw_rows_newline_at_r(S_STR_NUM, (const wchar_t**)s_strs, TIMER_FRAME_WIDTH, pos_x_wprint, pos_y_wprint);
    wdraw_newline();
}

static void doit_drawer_main_logic(const realtime_timer_t* timer, const draw_module_t* draw_module)
{
    // debug();

    const int timer_pos_x_wprint = draw_module->pos_x_wprint + 1;
    const int timer_pos_y_wprint = draw_module->pos_y_wprint + 3;

    wdraw_timer_frame_at(draw_module->pos_x_wprint, draw_module->pos_y_wprint);
    draw_module->draw_func(timer_pos_x_wprint, timer_pos_y_wprint, 0);

    int sec = 1;
    while (true) {
        int sig;
        int res = sigwait(&timer->sigset, &sig);
        if (res != 0) {
            handle_error_en("sigwait() error", res);
        }
        draw_module->draw_func(timer_pos_x_wprint, timer_pos_y_wprint, sec);
        sec += 1;
    }
}

static inline void cleanup_timer_drawer_module(realtime_timer_t* const out_timer)
{
    debug();

    my_assert(out_timer != NULL);

    if (timer_delete(out_timer->timerid) == -1) {
        handle_error("timer_delete() error");
    }
}

static void callback_cleanup_timer_drawer_module(void* arg)
{
    debug();

    realtime_timer_t* timer = (realtime_timer_t*)arg;
    cleanup_timer_drawer_module(timer);
}

static void init_timer(realtime_timer_t* const out_timer)
{
    debug();

    my_assert(out_timer->timersig == REALTIME_TIMER_SIG);

    /* Set sigset */
    sigemptyset(&out_timer->sigset);
    sigaddset(&out_timer->sigset, out_timer->timersig);

    /* Create timer */
    sigevent_t sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = out_timer->timersig;
    sev.sigev_value.sival_int = 0;
    sev._sigev_un._sigev_thread._function = NULL;
    if (timer_create(out_timer->clockid, &sev, &out_timer->timerid) == -1) {
        handle_error("timer_create() error");
    }
}

void init_timer_drawer(timer_drawer_t* const out_timer_drawer, int timersig)
{
    out_timer_drawer->timer.timersig = timersig;
}

void* run_timer_drawer_with(void* arg)
{
    debug();

    timer_drawer_t* timer_drawer = (timer_drawer_t*)arg;
    realtime_timer_t* timer = (realtime_timer_t*)&timer_drawer->timer;

    init_timer(timer);
    pthread_cleanup_push(callback_cleanup_timer_drawer_module, timer);

    /* Start timer */
    if (timer_settime(timer->timerid, 0, &timer->its, NULL) == -1) {
        handle_error("timer_settime() error");
    }

    doit_drawer_main_logic(timer, &timer_drawer->draw_module);

    cleanup_timer_drawer_module(timer);
    
    return NULL;
}

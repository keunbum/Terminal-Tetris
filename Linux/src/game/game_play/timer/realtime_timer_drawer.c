#include <signal.h>
#include <stddef.h>
#include <time.h>
#include <unistd.h>

#include "debug/debug.h"
#include "draw_tool/cursor.h"
#include "game/game_play/signal/signal_macro.h"
#include "game/game_play/timer/realtime_timer_drawer.h"
#include "game/game_play/ui/game_play_ui.h"

#define REALTIME_TIMER_FRAME_CORNER_TOP_LEFT (L'┌')
#define REALTIME_TIMER_FRAME_CORNER_TOP_RIGHT (L'┐')
#define REALTIME_TIMER_FRAME_CORNER_BOT_LEFT (L'└')
#define REALTIME_TIMER_FRAME_CORNER_BOT_RIGHT (L'┘')

#define REALTIME_TIMER_FRAME_HOR_UNIT (L'─')
#define REALTIME_TIMER_FRAME_VER_UNIT (L'│')
#define REALTIME_TIMER_FRAME_SPACE_UNIT (L' ')

#define TIMER_FRAME_WIDTH (14)

#define REALTIME_TIMER_SIG SIGRTMIN

//#define REALTIME_TIMER_CLOCK_ID CLOCK_PROCESS_CPUTIME_ID
//#define REALTIME_TIMER_CLOCK_ID CLOCK_THREAD_CPUTIME_ID
#define REALTIME_TIMER_CLOCK_ID CLOCK_REALTIME

#define REALTIME_TIMER_WAIT_TIME_SEC (0)
#define REALTIME_TIMER_WAIT_TIME_NSEC (0)

static void draw_timer_frame_at(int pos_x, int pos_y)
{
    static wchar_t S_TOP_LINE[TIMER_FRAME_WIDTH + 1];
    static wchar_t S_MID_LINE[TIMER_FRAME_WIDTH + 1];
    static wchar_t S_BOT_LINE[TIMER_FRAME_WIDTH + 1];
    static wchar_t* S_STRS[] = { S_TOP_LINE, S_MID_LINE, S_BOT_LINE };
    static const int S_STR_NUM = 3;

    set_row_line(S_TOP_LINE, TIMER_FRAME_WIDTH, REALTIME_TIMER_FRAME_CORNER_TOP_LEFT, REALTIME_TIMER_FRAME_HOR_UNIT, REALTIME_TIMER_FRAME_CORNER_TOP_RIGHT);
    set_row_line(S_MID_LINE, TIMER_FRAME_WIDTH, REALTIME_TIMER_FRAME_VER_UNIT, REALTIME_TIMER_FRAME_SPACE_UNIT, REALTIME_TIMER_FRAME_VER_UNIT);
    set_row_line(S_BOT_LINE, TIMER_FRAME_WIDTH, REALTIME_TIMER_FRAME_CORNER_BOT_LEFT, REALTIME_TIMER_FRAME_HOR_UNIT, REALTIME_TIMER_FRAME_CORNER_BOT_RIGHT);

    wgotoxy(pos_x, pos_y);
    for (int i = 0; i < S_STR_NUM; ++i) {
        draw_row_cursor_newline(S_STRS[i], TIMER_FRAME_WIDTH);
    }
}

static void handle_timer_sig(int sig)
{
    debug();
    /* do nothing */
}

/* Actually, it's not a proper implementation,
   because the 'run_realtime_timer_with' function is not executed in parallel.
   Perhaps you should use a timer-related system call.. Search a lot.
   ref: https://man7.org/linux/man-pages/man2/timer_create.2.html
        https://man7.org/linux/man-pages/man2/alarm.2.html
        https://man7.org/linux/man-pages/man3/clock_gettime.3.html
 */
/*
void* run_realtime_timer_drawer_with(void* arg)
{
    debug();

    const realtime_timer_data_t* timer_data_ptr = (realtime_timer_data_t*)arg;
    const draw_module_t* draw_module_ptr = &timer_data_ptr->draw_module;
    const int pos_x = draw_module_ptr->pos_x;
    const int pos_y = draw_module_ptr->pos_y;

    draw_timer_frame_at(pos_x, pos_y);
    for (int i = 0; i < timer_data_ptr->time_limit; ++i) {
        const int time_pos_x = pos_x + 1;
        const int time_pos_y = pos_y + 3;

        draw_module_ptr->draw_func(time_pos_x, time_pos_y, i + 1);
        sleep(draw_module_ptr->tspec.tv_sec);
    }
    return NULL;
}*/

void* new_run_realtime_timer_drawer_with(void* arg)
{
    debug();

    const realtime_timer_data_t* timer_data_ptr = (realtime_timer_data_t*)arg;
    const draw_module_t* draw_module_ptr = &timer_data_ptr->draw_module;
    const int timer_pos_x = draw_module_ptr->pos_x + 1;
    const int timer_pos_y = draw_module_ptr->pos_y + 3;

    draw_timer_frame_at(draw_module_ptr->pos_x, draw_module_ptr->pos_y);
    draw_module_ptr->draw_func(timer_pos_x, timer_pos_y, 0);

    /* Block the timer's signal if necessary */

    /* Set handler for timer signal */
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = handle_timer_sig;
    sigemptyset(&sa.sa_mask);
    if (sigaction(REALTIME_TIMER_SIG, &sa, NULL) == -1) {
        handle_error("sigaction() error");
    }

    /* Set sigset */
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, REALTIME_TIMER_SIG);

    /* Create timer */
    sigevent_t sev;
    timer_t timerid;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = REALTIME_TIMER_SIG;
    sev.sigev_value.sival_int = 0;
    sev._sigev_un._sigev_thread._function = NULL;
    if (timer_create(REALTIME_TIMER_CLOCK_ID, &sev, &timerid) == -1) {
        handle_error("timer_create() error");
    }

    /* Start timer */
    if (timer_settime(timerid, 0, &draw_module_ptr->its, NULL) == -1) {
        handle_error("timer_settime() error");
    }

    /* Run main logic */
    for (int i = 0; i < timer_data_ptr->time_limit; ++i) {
        draw_module_ptr->draw_func(timer_pos_x, timer_pos_y, i + 1);
        int sig;
        int res = sigwait(&sigset, &sig);
        my_assert(sig == REALTIME_TIMER_SIG);
        if (res != 0) {
            handle_error_en(res, "sigwait() error");
        }
    }

    return NULL;
}
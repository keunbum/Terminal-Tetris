#include <signal.h>
#include <stddef.h>
#include <time.h>
#include <unistd.h>

#include "debug/debug.h"
#include "draw_tool/cursor.h"
#include "game/game_play/signal/signal_macro.h"
#include "game/game_play/ui/game_play_ui.h"
#include "realtime_timer_drawer.h"

#define REALTIME_TIMER_FRAME_CORNER_TOP_LEFT (L'┌')
#define REALTIME_TIMER_FRAME_CORNER_TOP_RIGHT (L'┐')
#define REALTIME_TIMER_FRAME_CORNER_BOT_LEFT (L'└')
#define REALTIME_TIMER_FRAME_CORNER_BOT_RIGHT (L'┘')

#define REALTIME_TIMER_FRAME_HOR_UNIT (L'─')
#define REALTIME_TIMER_FRAME_VER_UNIT (L'│')
#define REALTIME_TIMER_FRAME_SPACE_UNIT (L' ')

#define TIMER_FRAME_WIDTH (14)

#define REALTIME_TIMER_CLOCK_ID CLOCK_REALTIME

#define REALTIME_TIMER_WAIT_TIME_SEC (0)
#define REALTIME_TIMER_WAIT_TIME_NSEC (0)

atomic_bool g_realtime_timer_running;

static void wdraw_timer_frame_at(int pos_x, int pos_y)
{
    debug();

    static wchar_t s_top_line[TIMER_FRAME_WIDTH + 1];
    static wchar_t s_mid_line[TIMER_FRAME_WIDTH + 1];
    static wchar_t s_bot_line[TIMER_FRAME_WIDTH + 1];
    static wchar_t* s_strs[] = { s_top_line, s_mid_line, s_bot_line };
    static const int S_STR_NUM = 3;

    wset_row_line(s_top_line, TIMER_FRAME_WIDTH, REALTIME_TIMER_FRAME_CORNER_TOP_LEFT, REALTIME_TIMER_FRAME_HOR_UNIT, REALTIME_TIMER_FRAME_CORNER_TOP_RIGHT);
    wset_row_line(s_mid_line, TIMER_FRAME_WIDTH, REALTIME_TIMER_FRAME_VER_UNIT, REALTIME_TIMER_FRAME_SPACE_UNIT, REALTIME_TIMER_FRAME_VER_UNIT);
    wset_row_line(s_bot_line, TIMER_FRAME_WIDTH, REALTIME_TIMER_FRAME_CORNER_BOT_LEFT, REALTIME_TIMER_FRAME_HOR_UNIT, REALTIME_TIMER_FRAME_CORNER_BOT_RIGHT);

    wdraw_rows_newline_at_r(S_STR_NUM, s_strs, TIMER_FRAME_WIDTH, pos_x, pos_y);
}

void* run_realtime_timer_drawer_with(void* arg)
{
    debug();

    const realtime_timer_data_t* timer_data_ptr = (realtime_timer_data_t*)arg;
    const draw_module_t* draw_module_ptr = &timer_data_ptr->draw_module;
    const int timer_pos_x = draw_module_ptr->pos_x + 1;
    const int timer_pos_y = draw_module_ptr->pos_y + 3;

    wdraw_timer_frame_at(draw_module_ptr->pos_x, draw_module_ptr->pos_y);
    draw_module_ptr->draw_func(timer_pos_x, timer_pos_y, 0);

    /* Set sigset */
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, REALTIME_TIMER_SIG);

    /* Create timer */
    sigevent_t sev;
    timer_t timer_id;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = REALTIME_TIMER_SIG;
    sev.sigev_value.sival_int = 0;
    sev._sigev_un._sigev_thread._function = NULL;
    if (timer_create(REALTIME_TIMER_CLOCK_ID, &sev, &timer_id) == -1) {
        handle_error("timer_create() error");
    }

    /* Start timer */
    if (timer_settime(timer_id, 0, &draw_module_ptr->its, NULL) == -1) {
        handle_error("timer_settime() error");
    }

    /* Run main logic */
    g_realtime_timer_running = ATOMIC_VAR_INIT(true);
    for (int sec = 1; sec <= timer_data_ptr->time_limit; ++sec) {
        if (!atomic_load(&g_realtime_timer_running)) {
            break;
        }
        int sig;
        int res = sigwait(&sigset, &sig);
        if (res != 0) {
            handle_error_en(res, "sigwait() error");
        }
        const draw_module_t* draw_module_ptr = &timer_data_ptr->draw_module;
        const int timer_pos_x = draw_module_ptr->pos_x + 1;
        const int timer_pos_y = draw_module_ptr->pos_y + 3;
        draw_module_ptr->draw_func(timer_pos_x, timer_pos_y, sec);
    }
    g_realtime_timer_running = ATOMIC_VAR_INIT(false);
    timer_delete(timer_id);
    ewprintf("run_realtime_timer_drawer_with() return NULL\n");
    return NULL;
}
#include "game_play_timer.h"
#include "debug.h"
#include "draw/draw_tool.h"
#include "pthread_macro.h"

static void do_game_play_timer_routine(const game_play_timer_t* game_play_timer)
{
    const realtime_timer_t* timer = &game_play_timer->realtime_timer;

    run_game_play_timer_module(&game_play_timer->before_module);

    while (true) {
        int sig;
        int res = sigwait(&timer->sigset, &sig);
        if (res != 0) {
            handle_error_en("sigwait() error", res);
        }
        run_game_play_timer_module(&game_play_timer->main_module);
    }
}

static void callback_remove_realtime_timer(void* arg)
{
    realtime_timer_t* timer = (realtime_timer_t*)arg;
    remove_realtime_timer(timer);
}

void init_game_play_timer(game_play_timer_t* const out_game_play_timer, clockid_t clockid, int timersig, struct itimerspec its, game_play_timer_module_t before_module, game_play_timer_module_t main_module)
{
    init_realtime_timer(&out_game_play_timer->realtime_timer, clockid, timersig, its);
    out_game_play_timer->before_module = before_module;
    out_game_play_timer->main_module = main_module;
}

void cleanup_game_play_timer(game_play_timer_t* const out_game_play_timer)
{
    cleanup_realtime_timer(&out_game_play_timer->realtime_timer);
}

void* run_game_play_timer(void* arg)
{
    game_play_timer_t* const game_play_timer = (game_play_timer_t*)arg;
    realtime_timer_t* const timer = &game_play_timer->realtime_timer;

    register_realtime_timer(timer);
    pthread_cleanup_push(callback_remove_realtime_timer, timer);

    start_realtime_timer(timer);

    do_game_play_timer_routine(game_play_timer);

    pthread_cleanup_pop(1);

    return NULL;
}

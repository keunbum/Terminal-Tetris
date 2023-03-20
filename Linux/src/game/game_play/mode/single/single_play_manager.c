#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "debug/debug.h"
#include "error/error_handling.h"
#include "game/game_play/common/game_play_common.h"
#include "game/game_play/mode/single/single_play_manager.h"
#include "game/game_play/signal/signal_handler.h"
#include "game/game_play/timer/game_play_timer.h"
#include "game/game_play/timer/realtime_timer.h"
#include "game/game_play/ui/game_play_screen.h"
#include "game/game_play/ui/game_play_ui.h"
#include "util/util.h"

static sigset_t g_s_sigset;

static void handle_game_sub_modules(int sig)
{
    ewprintf("me: %d, p: %d, take_childproc(%d)\n", getpid(), getppid(), sig);
    assert(sig == SIGCHLD);
    int status;
    // pid_t pid = waitpid(-1, &status, WNOHANG);
    pid_t pid = waitpid(-1, &status, 0);
    ewprintf("proc-%d: exited.\n", pid);
    assert(pid != -1);
    assert(WIFEXITED(status));
    // ewprintf("Removed proc id: %d\n", pid);
    // ewprintf("Child send %d\n", );

    int exit_status;
    if ((exit_status = WEXITSTATUS(status)) == GAME_PLAY_STATUS_GAME_OVER) {
        return;
    }
    sigsuspend(&g_s_sigset);
}

static void load_game(void)
{
    debug();

    load_game_play_single_ui(GAME_PLAY_SCREEN_START_POS_X, GAME_PLAY_SCREEN_START_POS_Y, GAME_PLAY_SCREEN_HEIGHT);
}

static void execute_game_sub_module_in_parallel(const game_play_sub_module_t module, const void* arg)
{
    debug();

    /* It may be replaced with a thread method in the future.
       So keep maintainability. */
    pid_t pid = fork();
    if (pid == 0) {
        module((void*)arg);
        exit(EXIT_SUCCESS);
    }
}

static void execute_game_sub_modules_in_parallel(void)
{
    debug();

    static const game_play_sub_module_t s_module_main_funcs[] = { main_func_for_game_play_timer };
    static const realtime_timer_data_t s_timer_data = {
        .time_limit = GAME_PLAY_TIME_LIMIT,
        .draw_module = {
            .pos_x = GAME_PLAY_TIMER_POS_X,
            .pos_y = GAME_PLAY_TIMER_POS_Y,
            .unit_sec = GAME_PLAY_UNIT_SEC,
            .draw_func = draw_game_play_timer_at_with,
        },
    };
    static const void* s_args[] = { &s_timer_data };
    static const int S_GAME_MODULE_NUM = (int)(sizeof(s_module_main_funcs) / sizeof(s_module_main_funcs[0]));

    forn(i, S_GAME_MODULE_NUM) {
        execute_game_sub_module_in_parallel(s_module_main_funcs[i], s_args[i]);
    }
}

static int execute_game_main_module(void)
{
    // ...
    return GAME_PLAY_CMD_EXIT_GAME;
}

static int play_game(void)
{
    debug();

    static struct sigaction s_act;

    REGISTER_HANDLER_EMPTYSET_NOOACT(s_act, handle_game_sub_modules, 0, SIGCHLD);
    load_game();
    execute_game_sub_modules_in_parallel();
    return execute_game_main_module();
}

void* run_single_mode(void* arg)
{
    debug();

    while (true) {
        int status = play_game();
        if (status == GAME_PLAY_CMD_EXIT_GAME) {
            break;
        }
        if (status == GAME_PLAY_CMD_ERROR) {
            handle_error("run_single_play() error");
        }
    }
    return NULL;
}

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "debug/debug.h"
#include "draw_tool/cursor.h"
#include "error/error_handling.h"
#include "game/game_play/game_mode/single/single_play_manager.h"
#include "game/game_play/game_play.h"
#include "game/game_play/random/random.h"
#include "game/game_play/signal/signal_macro.h"
#include "game/game_play/simulate/simulate.h"
#include "game/game_play/tetromino/tetromino.h"
#include "game/game_play/timer/game_play_timer.h"
#include "game/game_play/timer/realtime_timer_drawer.h"
#include "game/game_play/ui/game_play_screen.h"
#include "game/game_play/ui/game_play_ui.h"

// static sigset_t g_s_sigset;

static void handle_game_play_sub_modules(int sig)
{
    ewprintf("me: %d, p: %d, take_childproc(%d)\n", getpid(), getppid(), sig);
    my_assert(sig == SIGCHLD);
    int status;
    // pid_t pid = waitpid(-1, &status, WNOHANG);
    pid_t pid = waitpid(-1, &status, 0);
    ewprintf("proc-%d: exited.\n", pid);
    my_assert(pid != -1);
    my_assert(WIFEXITED(status));
    if (!WIFEXITED(status)) {
        ewprintf("proc has no status\n");
        return;
    }
    int exit_status = WEXITSTATUS(status);
    my_assert(exit_status == GAME_PLAY_STATUS_GAME_OVER);
    return;
    /*
    if ((exit_status = WEXITSTATUS(status)) == GAME_PLAY_STATUS_GAME_OVER) {
        return;
    }
    sigsuspend(&g_s_sigset);
    */
}

static int load_game(void)
{
    debug();

    int res = load_game_play_ui(GAME_PLAY_MODE_SINGLE, GAME_PLAY_SCREEN_START_POS_X, GAME_PLAY_SCREEN_START_POS_Y, GAME_PLAY_SCREEN_HEIGHT);
    if (res == -1) {
        handle_error("load_game_play_ui() error");
    }
    return res;
}

/* -----------------------------------fork version------------------------------------ */

static void run_game_sub_module_in_parallel(const game_play_module_t module)
{
    debug();

    /* It may be replaced with a thread method in the future.
       So keep maintainability. */
    pid_t pid = fork();
    if (pid == 0) {
        module.func(module.arg);
        assert(false);
        exit(EXIT_SUCCESS);
    }
}

static int run_game_sub_modules_in_parallel(void)
{
    debug();

    // main_func_for_user_input_handler() should be added.
    // change_direction_based_on_user_input();
    // rotate_based_on_user_input();

    static const realtime_timer_data_t S_TIMER_DATA = {
        .time_limit = GAME_PLAY_TIME_LIMIT,
        .draw_module = {
            .pos_x = GAME_PLAY_TIMER_POS_X,
            .pos_y = GAME_PLAY_TIMER_POS_Y,
            .its.it_value.tv_sec = GAME_PLAY_TIMER_INIT_EXPIRE_SEC,
            .its.it_value.tv_nsec = GAME_PLAY_TIMER_INIT_EXPIRE_NSEC,
            .its.it_interval.tv_sec = GAME_PLAY_TIMER_INTERVAL_SEC,
            .its.it_interval.tv_nsec = GAME_PLAY_TIMER_INTERVAL_NSEC,
            .draw_func = draw_game_play_timer_at_with,
        },
    };
    static const game_play_module_t S_GAME_PLAY_MODULES[] = {
        {
            main_func_for_game_play_timer,
            (void*)&S_TIMER_DATA,
        },
    };

    static const size_t S_GAME_MODULE_NUM = (size_t)(sizeof(S_GAME_PLAY_MODULES) / sizeof(S_GAME_PLAY_MODULES[0]));

    struct sigaction s_act;
    REGISTER_HANDLER_EMPTYSET_NOOACT(s_act, handle_game_play_sub_modules, 0, SIGCHLD);

    for (size_t i = 0; i < S_GAME_MODULE_NUM; ++i) {
        run_game_sub_module_in_parallel(S_GAME_PLAY_MODULES[i]);
    }
    return 0;
}

static int run_game_main_module(void)
{
    debug();

    /* Not a good logic yet. There is a possibility of change,
       but first of all, I will write the code sequentially. */
    init_rng((unsigned int)time(NULL));

    while (true) {
        tetromino_t tetromino_obj = {
            .tetromino_id = rng() % TOTAL_TETROMINO_NUM,
            .pos_x = GAME_PLAY_INIT_TETROMINO_POS_X,
            .pos_y = GAME_PLAY_INIT_TETROMINO_POS_Y,
            .velocity = GAME_PLAY_INIT_TETROMINO_VELOCITY,
            .dir = DIR_BOT,
            .color = COLOR_BLACK,
        };
        /* Uh.. I think.. The concept of speed should be defined like this,
           "Every few frames it goes down by one block." */
        while (true) {
            // draw_over_all(); ->
            // handle_user_input();
            move_tetromino(&tetromino_obj);
            /*
            if (tetromino_is_stopped()) {
                clear_filled_lines(); --> reflect_them_visually(); : maybe internally.
                break;
            } */
            usleep(16666);
        }
    }
    return GAME_PLAY_STATUS_GAME_OVER;
}

static int play_game(void)
{
    debug();

    int res = GAME_PLAY_CMD_ERROR;

    if ((res = load_game()) == -1) {
        handle_error("load_game() error");
    }
    if ((res = run_game_sub_modules_in_parallel()) == -1) {
        handle_error("execute_game_sub_modules_in_parallel() error");
    };
    if ((res = run_game_main_module() == -1)) {
        handle_error("execute_game_main_module() error");
    };

    return res;
}

/* -------------------------------Will be replaced with threaded version------------------------------- */

static void run_game_play_module_in_parallel(const game_play_module_t module)
{
    debug();

    // do smth..
}

static void run_game_play_modules_in_parallel(void)
{
    debug();

    static const realtime_timer_data_t S_TIMER_DATA = {
        .time_limit = GAME_PLAY_TIME_LIMIT,
        .draw_module = {
            .pos_x = GAME_PLAY_TIMER_POS_X,
            .pos_y = GAME_PLAY_TIMER_POS_Y,
            .its.it_value.tv_sec = GAME_PLAY_TIMER_INIT_EXPIRE_SEC,
            .its.it_value.tv_nsec = GAME_PLAY_TIMER_INIT_EXPIRE_NSEC,
            .its.it_interval.tv_sec = GAME_PLAY_TIMER_INTERVAL_SEC,
            .its.it_interval.tv_nsec = GAME_PLAY_TIMER_INTERVAL_NSEC,
            .draw_func = draw_game_play_timer_at_with,
        },
    };
    static const game_play_module_t S_GAME_PLAY_MODULES[] = {
        {
            main_func_for_game_play_timer,
            &S_TIMER_DATA,
        },
    };
    static const size_t S_GAME_PLAY_MODULE_NUM = (size_t)(sizeof(S_GAME_PLAY_MODULES) / sizeof(S_GAME_PLAY_MODULES[0]));

    // hmm..
    // struct sigaction s_act;
    // REGISTER_HANDLER_EMPTYSET_NOOACT(s_act, handle_game_play_sub_modules, 0, SIGCHLD);

    for (size_t i = 0; i < S_GAME_PLAY_MODULE_NUM; ++i) {
        run_game_play_module_in_parallel(S_GAME_PLAY_MODULES[i]);
    }
}

static int ready_getset_go(int sec)
{
    /* not yet */
    debug();

    return 0;
}

static int run_simulation(void)
{
    debug();

    ready_getset_go(GAME_PLAY_TIMEINTERVAL_BEFORESTART_SEC);
    run_game_play_modules_in_parallel();

    // may be smth needed..

    return 0;
}

static int start_game(void)
{
    debug();

    int res;

    if ((res = ready_getset_go(GAME_PLAY_TIMEINTERVAL_BEFORESTART_SEC)) == -1) {
        handle_error("ready_getset_go() error");
    }
    if ((res = run_simulation()) == -1) {
        handle_error("run_simulation() error");
    }
    return res;
}

static int new_play_game(void)
{
    debug();

    int res = GAME_PLAY_CMD_ERROR;

    if ((res = load_game()) == -1) {
        handle_error("load_game() error");
    }
    if ((res = start_game() == -1)) {
        handle_error("start_simulation() error");
    }
    return res;
}

/* --------------------------------------------------------------------------------------------------------- */

void* run_single_mode(void* arg)
{
    debug();

    while (true) {
        int status = play_game();
        // int status = new_play_game();
        if (status == GAME_PLAY_CMD_EXIT_GAME) {
            break;
        }
        if (status == GAME_PLAY_CMD_ERROR) {
            handle_error("run_single_play() error");
        }
    }
    return NULL;
}

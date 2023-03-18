#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "debug/debug.h"
#include "error/error_handling.h"
#include "game/draw_manager/cursor.h"
#include "game/draw_manager/draw_manager.h"
#include "game/game_manager/game_manager.h"
#include "game/game_manager/menu.h"
#include "game/game_play/game_play_manager.h"
#include "game/game_play/game_play_screen.h"
#include "game/game_play/game_play_timer.h"
#include "game/tetromino/tetromino_manager.h"
#include "util/util.h"

#define REGISTER_HANDLER_EMPTYSET(_act, _handler, _sa_flags, _sig_num, _oact) \
    do {                                                                      \
        _act.sa_handler = _handler;                                           \
        sigemptyset(&_act.sa_mask);                                           \
        _act.sa_flags = _sa_flags;                                            \
        sigaction(_sig_num, &_act, &o_act);                                   \
    } while (false)

#define REGISTER_HANDLER_EMPTYSET_NOOACT(_act, _handler, _sa_flags, _sig_num) \
    do {                                                                      \
        _act.sa_handler = _handler;                                           \
        sigemptyset(&_act.sa_mask);                                           \
        _act.sa_flags = _sa_flags;                                            \
        sigaction(_sig_num, &_act, 0);                                        \
    } while (false)

#define GAME_MODULE_NUM (2)

static sigset_t g_s_sigset;

static void handle_childproc(int sig)
{
    ewprintf("me: %d, p: %d, take_childproc(%d)\n", getpid(), getppid(), sig);
    assert(sig == SIGCHLD);
    int status;
    //pid_t pid = waitpid(-1, &status, WNOHANG);
    pid_t pid = waitpid(-1, &status, 0);
    ewprintf("proc-%d: exited.\n", pid);
    assert(pid != -1);
    assert(WIFEXITED(status));
    // ewprintf("Removed proc id: %d\n", pid);
    // ewprintf("Child send %d\n", );

    int exit_status;
    if ((exit_status = WEXITSTATUS(status)) == EXIT_GAME_OVER) {
        return;
    }
    sigsuspend(&g_s_sigset);
}

static void load_ui(void)
{
    debug();

    draw_whole_screen_at(GAME_PLAY_SCREEN_START_POS_X, GAME_PLAY_SCREEN_START_POS_Y);
    // draw_a_default_tetromino_at(0, 20, 20);
    fflush(stdout);
    wgotoxy(GAME_PLAY_SCREEN_START_POS_X + GAME_PLAY_SCREEN_HEIGHT + 1, 0);
}

static void load_game(void)
{
    debug();

    load_ui();
}

static void execute_game_module_in_parallel(const module_t module, const void* arg)
{
    debug();

    /* It may be replaced with a thread method in the future.
       So keep maintainability. */
    pid_t pid = fork();
    if (pid == 0) {
        module((void*) arg);
        exit(EXIT_SUCCESS);
    }
}

static void execute_game_modules_in_parallel(void)
{
    debug();
//    ewprintf("me: %d, p: %d, run_game()\n", getpid(), getppid());

    static const module_t s_module_ignite_funcs[GAME_MODULE_NUM] = {run_game_play_timer, start_game};
    static const int s_args[] = {GAME_PLAY_TIME_LIMIT, 0};
    forn (i, GAME_MODULE_NUM) {
        execute_game_module_in_parallel(s_module_ignite_funcs[i], &s_args[i]);
        // ewprintf("%dth loop, child's pid: %d\n", i, pid);
    }
}

/*
static pthread_t threads[2];
static void execute_game_module_in_parallel_by_thread(const module_t module, const void* arg)
{
    debug();


}

static void execute_game_modules_in_parallel_by_thread(void)
{
    debug();

    static const module_t s_module_ignite_funcs[GAME_MODULE_NUM] = {run_game_play_timer, start_game};
    static const int s_args[] = {GAME_PLAY_TIME_LIMIT, 0};
    forn (i, GAME_MODULE_NUM) {
        execute_game_module_in_parallel(s_module_ignite_funcs[i], &s_args[i]);
        //execute_game_module_in_parallel_by_thread(s_module_ignite_funcs[i], &s_args[i]);
        //ewprintf("%dth loop, child's pid: %d\n", i, pid);
    }
}
*/

static void wait_modules(void)
{
    /* Now, I use sigsuspend,
       but when I searched, there were sigwait, sigwaitinfo, etc.
       You need to read the ref docs properly and use the appropriate system call. */
    /* Of course, you may use the thread method. */
    sigsuspend(&g_s_sigset);
}

static void run_game(void)
{
    debug();

    static struct sigaction s_act;
    REGISTER_HANDLER_EMPTYSET_NOOACT(s_act, handle_childproc, 0, SIGCHLD);
    load_game();
    execute_game_modules_in_parallel();
    wait_modules();
    ewprintf("Parent-%d took all of the %d waiting child modules.\n", getpid(), GAME_MODULE_NUM);
}

static void exit_game(void)
{
    debug();
    /* It might need some cleanup module later. */
}

static void handle_cmd(int cmd)
{
    debug();

    switch (cmd) {
    case TITLE_MENU_CMD_START_GAME:
        run_game();
        break;
    case TITLE_MENU_CMD_EXIT_GAME:
        exit_game();
        break;
    case TITLE_MENU_CMD_ERROR:
        handle_error("Reading input faild.");
        break;
    default:
        handle_error("Not a valid menu cmd.");
        break;
    }
}

void run_title_menu(void)
{
    debug();

    /* Right now it's accepting options in scanf format,
       but in the future I'd like to be able to navigate through the options with the arrow keys.
       For example create_drawer()?
       It would be better to run separate modules for drawing on the screen and receiving input. */
    draw_title_menu_screen();
    int cmd = read_title_menu_option();
    handle_cmd(cmd);
}

/*
 * You actually read the stuff from the bottom.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "debug/debug.h"
#include "error/error_handling.h"
#include "game/game_manager/game_manager.h"
#include "game/game_manager/menu.h"
#include "game/game_play/game_play_screen.h"
#include "game/game_play/game_play_timer.h"
#include "game/tetromino/tetromino_manager.h"
#include "util/util.h"

static sigset_t sigset;

static void childproc_handler(int sig)
{
    ewprintf("me: %d, p: %d, take_childproc(%d)\n", getpid(), getppid(), sig);
    my_assert(sig == SIGCHLD);
    int status;
    // pid_t pid = waitpid(-1, &status, WNOHANG);
    pid_t pid = waitpid(-1, &status, 0);
    ewprintf("proc-%d: exited.\n", pid);
    my_assert(pid != -1);
    my_assert(WIFEXITED(status));
    // ewprintf("Removed proc id: %d\n", pid);
    // ewprintf("Child send %d\n", );

    int exit_status = WEXITSTATUS(status);
    if (exit_status == EXIT_GAME_OVER)
    {
        return;
    }
    sigsuspend(&sigset);
}

static void load_ui(void)
{
    debug();
    draw_whole_screen_at(GAME_PLAY_SCREEN_START_POS_X, GAME_PLAY_SCREEN_START_POS_Y);
    fflush(stdout);
    //draw_a_default_tetromino_at(0, 20, 20);
    wgotoxy(GAME_PLAY_SCREEN_START_POS_X + GAME_PLAY_SCREEN_HEIGHT + 1, 0);
}

static void load_game(void)
{
    debug();
    load_ui();
}

static void start_game(const void *arg)
{
    debug();
    // hmm..
    (void)arg;
}

#define CHLD_PROCESS_NUM (2)

static void execute_game_modules(void)
{
    debug();

    static const module_t process_start_funcs[] = {run_game_play_timer, start_game};
    static const int args[] = {GAME_PLAY_TIME_LIMIT, 0};

    ewprintf("me: %d, p: %d, run_game()\n", getpid(), getppid());

    forn(i, CHLD_PROCESS_NUM)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            process_start_funcs[i](&args[i]);
            exit(0);
        }
        ewprintf("%dth loop, child's pid: %d\n", i, pid);
    }
}

#define REGISTER_HANDLER(_act, _handler, _sa_flags, _sig_num, _oact) \
    do                                                               \
    {                                                                \
        _act.sa_handler = _handler;                                  \
        _act.sa_flags = _sa_flags;                                   \
        sigaction(_sig_num, &_act, &o_act);                          \
    } while (false)

#define REGISTER_HANDLER_NO_OACT(_act, _handler, _sa_flags, _sig_num) \
    do                                                                \
    {                                                                 \
        _act.sa_handler = _handler;                                   \
        _act.sa_flags = _sa_flags;                                    \
        sigaction(_sig_num, &_act, 0);                                \
    } while (false)

static void run_game(void)
{
    debug();

    static struct sigaction act;
    REGISTER_HANDLER_NO_OACT(act, childproc_handler, 0, SIGCHLD);

    load_game();
    execute_game_modules();

    sigemptyset(&sigset);
    sigsuspend(&sigset);
    ewprintf("Parent-%d escaped from all of the %d waiting childprocs.\n", getpid(), CHLD_PROCESS_NUM);
}

static void handle_cmd(int cmd)
{
    debug();
    switch (cmd)
    {
    case MENU_CMD_START_GAME:
        ewprintf("GAME STARTED\n");
        run_game();
        break;
    case MENU_CMD_EXIT_GAME:
        ewprintf("GAME EXITED\n");
        break;
    case MENU_CMD_ERROR:
        error_handling("Read input faild.");
        break;
    default:
        error_handling("Not a valid menu cmd.");
        break;
    }
}

void run_title_menu(void)
{
    debug();
    draw_menu_screen();
    // create_drawer()?
    // would be better to run separate process for drawing on the screen and receiving input.
    int cmd = read_menu_option();
    handle_cmd(cmd);
}

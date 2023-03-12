#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "debug/local_debug.h"
#include "game_manager/game_manager.h"
#include "util/util.h"
#include "tetromino/tetromino_manager.h"
#include "game_manager/menu.h"
#include "error/error_handling.h"
#include "game_play/game_play_screen.h"
#include "game_play/game_play_timer.h"

static sigset_t sigset;

static void childproc_handler(int sig)
{
    ewprintf("me: %d, p: %d, take_childproc(%d)\n", getpid(), getppid(), sig);
    Assert(sig == SIGCHLD);
    int status;
    //pid_t pid = waitpid(-1, &status, WNOHANG);
    pid_t pid = waitpid(-1, &status, 0);
    ewprintf("proc-%d: exited.\n", pid);
    Assert(pid != -1);
    Assert(WIFEXITED(status));
    //ewprintf("Removed proc id: %d\n", pid);
    //ewprintf("Child send %d\n", );

    int exit_status = WEXITSTATUS(status);
    if (exit_status == EXIT_GAME_OVER)
    {
        return;
    }
    sigsuspend(&sigset);
}

static void load_ui(void)
{
    draw_whole_screen_at(GAME_PLAY_SCREEN_START_POS_X, GAME_PLAY_SCREEN_START_POS_Y);
    draw_a_default_tetromino_at(0, 20, 20);
    wgotoxy(GAME_PLAY_SCREEN_START_POS_X + GAME_PLAY_SCREEN_HEIGHT + 1, 0);
}


static void load_game(void)
{
    load_ui();
}

static void start_game(const void* arg)
{
    // hmm..
    (void) arg;
}

#define CHLD_PROCESS_NUM (2)

static void execute_game_modules(void)
{

    static const module_t process_funcs[] = { run_game_play_timer, start_game };
    static const int args[] = { GAME_PLAY_TIME_LIMIT, 0 };

    ewprintf("me: %d, p: %d, run_game()\n", getpid(), getppid());

    forn(i, CHLD_PROCESS_NUM)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            process_funcs[i](&args[i]);
            exit(0);
        }
        ewprintf("%dth loop, child's pid: %d\n", i, pid);
    }
}

static void run_game(void)
{
    static struct sigaction act;
    act.sa_handler = childproc_handler;
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);
    sigemptyset(&sigset);

    load_game();
    execute_game_modules();

    sigsuspend(&sigset);
    ewprintf("Parent-%d escaped from all of the %d waiting childprocs.\n", getpid(), CHLD_PROCESS_NUM);
}

static void handle_cmd(int cmd)
{
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
    draw_menu_screen();
    // create_drawer()?
    // would be better to run separate process for drawing on the screen and receiving input.
    int cmd = read_menu_option();
    handle_cmd(cmd);
}


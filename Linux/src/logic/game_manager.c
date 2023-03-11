#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "debug/local_debug.h"
#include "logic/game_manager.h"
#include "util/util.h"
#include "ui/hud.h"
#include "tetromino/tetromino_manager.h"

static sigset_t sigset;

void take_childproc(int sig)
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

#define OPTION_NUM (2)

void menu(void)
{
    while (true)
    {
        static const char *options_text[OPTION_NUM] = { "start", "exit" };
        wprintf(L"TETRIS\n");
        forn(i, OPTION_NUM)
        {
            if (i > 0)
            {
                wprintf(L"  ");
            }
            wprintf(L"%d) %s", i + 1, options_text[i]);
        }
        wprintf(L"\n");

        bool ok = true;
        int cmd;
        scanf("%d", &cmd);
        switch (cmd)
        {
        case 1:
            return;
            break;
        case 2:
            exit(0);
            //return 1;
        default:
            ok = false;
            break;
        }
        if (ok)
        {
            break;
        }
    }
}


void load_game(void)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        draw_whole_screen_at(SCREEN_START_X, SCREEN_START_Y);
        draw_a_default_tetromino_at(0, 20, 20);
        exit(0);
    }
    wgotoxy(SCREEN_START_X + SCREEN_HEIGHT + 1, 0);
    int status;
    waitpid(pid, &status, 0);
}

int start_game(void)
{
    static struct sigaction act;
    act.sa_handler = take_childproc;
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    static const module_t funcs[] = { run_draw_time_at, simulate_tetrominos };
    static const int CHLD_PROCESS_NUM = sizeof(funcs) / sizeof(funcs[0]);
    ewprintf("me: %d, p: %d, start_game()\n", getpid(), getppid());
    forn(i, CHLD_PROCESS_NUM)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            funcs[i]();
            exit(0);
        }
        ewprintf("child's pid: %d\n", pid);
    }
    sigemptyset(&sigset);    
    sigsuspend(&sigset);
    ewprintf("Parent %d here\n", getpid());
    wgotoxy(SCREEN_START_X + SCREEN_HEIGHT + 1, 0);
    return 0;
}
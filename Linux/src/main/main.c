#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "game_manager/game_manager.h"
#include "error/error_handling.h"
#include "debug/local_debug.h"
#include "draw/cursor.h"

static void init_localize(void)
{
    setlocale(LC_CTYPE, "");
}

static void init(void)
{
    init_localize();
}

static void main2(void)
{
    init();
    run_title_menu();

    wgotoxy(GAME_CONSOLE_STDOUT_POS_X + 1, GAME_CONSOLE_STDOUT_POS_Y);
    ewprintf("GAME ENDED.\n");
}

static int test(void);

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        if (strcmp(argv[1], "-test") == 0)
        {
            test();
            return 0;
        }
        error_handling("Not a valid argument.");
    }
    if (argc != 1)
    {
        printf("usage: ./%s\n", argv[0]);
        return 1;
    }
    main2();
    return 0;
}

static int test(void)
{
    while (false)
    {
        //char ch = getch();

    }
    return 0;
}
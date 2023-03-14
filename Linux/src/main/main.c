#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "debug/debug.h"
#include "game/draw_manager/cursor.h"
#include "error/error_handling.h"
#include "game/game_manager/game_manager.h"
#include "test/test.h"

static void init_localize(void)
{
    debug();
    setlocale(LC_CTYPE, "");
}

static void init(void)
{
    debug();
    init_localize();
}

static void main2(void)
{
    debug();
    init();
    run_title_menu();

    wgotoxy(GAME_CONSOLE_STDOUT_POS_X + 1, GAME_CONSOLE_STDOUT_POS_Y);
    ewprintf("GAME ENDED.\n");
}

int main(int argc, char *argv[])
{
    debug();
    if (argc == 2)
    {
        if (strcmp(argv[1], "-test") == 0)
        {
            test();
            return 0;
        }
        handle_error("Not a valid argument.");
    }
    if (argc != 1)
    {
        printf("usage: ./%s\n", argv[0]);
        return 1;
    }
    main2();
    return 0;
}

/*
 * You actually read the stuff from the bottom.

 * basic strategy:
  * read it as if you were wrong once. --> "why is this wrong??"
  * simplify. a step-by-step approach
  * readability is important
  * think rationally. keep calm
  * WRITE STUFF DOWN
  * DON'T GET STUCK ON ONE APPROACH
  
 * stuff you should look for
  * special cases (n=1?)
  * invalid pointer operation
  * invalid argument passing
*/
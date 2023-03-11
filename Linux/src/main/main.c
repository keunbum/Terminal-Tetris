#include <assert.h>
//#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "tetromino/color.h"
#include "draw/cursor.h"
#include "draw/draw_manager.h"
#include "logic/game_manager.h"
#include "debug/local_debug.h"
#include "tetromino/tetromino.h"
#include "util/util.h"

static void main2(void);
static int test(void);

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        if (strcmp(argv[1], "-test"))
        {
            test();
            return 0;
        }
    }
    if (argc != 1)
    {
        printf("usage: ./%s\n", argv[0]);
        return 1;
    }
    main2();
    return 0;
}

static void init(void)
{
    setlocale(LC_CTYPE, "");
}


static void main2(void)
{
    init();
    menu();
    load_game();
    int res = start_game();
    Assert(res == 0);
    ewprintf("GAME ENDED\n");
}

static int test(void)
{
    while (true)
    {
        char ch = getch();

    }
}
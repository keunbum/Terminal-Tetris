#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <locale.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "color.h"
#include "cursor.h"
#include "draw_manager.h"
#include "game_manager.h"
#include "local_debug.h"
#include "tetromino.h"
#include "util.h"

void main2(void);
//static int test(char *[]);

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        printf("usage: ./%s\n", argv[0]);
        return 1;
    }
    main2();
    return 0;
}

void init(void)
{
    setlocale(LC_CTYPE, "");
}


void main2(void)
{
    init();
    menu();
    load_game();
    int res = start_game();
    Assert(res == 0);
    ewprintf("GAME ENDED\n");
}

/*
static int test(char *argv[])
{
    {
        forn(i, TETROMINO_COUNT)
        {
            tetromino_t t = {
                .tetromino_id = i,
                .dir = DIR_BOT,
                .color = COLOR_WHITE,
            };
        }
    }
    {
        wclear();
        wprintf(
            L"Enter your number in the box below\n"\
            "+-----------------+\n"\
            "|                 |\n"\
            "+-----------------+\n"
        );
        int x = 2;
        int y = 1;
        wgotoxy(x, y);
        forn(i, 20)
        {
            putwc('*', stdout);
            fflush(stdout);
            usleep((useconds_t)1e5);
            wgotoxy(x, y);
            putwc(' ', stdout);
            y += 1;
        }
        wgotoxy(4, 0);
    }
    return 0;
} */

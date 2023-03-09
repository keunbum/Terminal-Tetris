#include <stdio.h>
#include <unistd.h>
#include <locale.h>

#include "color.h"
#include "cursor.h"
#include "tetromino.h"
#include "util.h"

static void init(void);
static void main2(void);
static int test(char *[]);

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

static void init(void)
{
    setlocale(LC_CTYPE, "");
}

static void main2(void)
{
    init();

    FORN(i, TETROMINO_COUNT)
    {
        tetromino_t t = {
            .polyomino_id = i,
            .dir = DIR_BOT,
            .color = COLOR_WHITE,
        };
        print_tetromino(&t);
    }
}

static int test(char *argv[])
{
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
        for (int i = 0; i < 20; ++i)
        {
            putwc('*', stdout);
            fflush(stdout);
            usleep((useconds_t)1e5);
            wgotoxy(x, y);
            putwc(' ', stdout);
            y += 1;
        }
        gotoxy(4, 0);
    }
    return 0;
}


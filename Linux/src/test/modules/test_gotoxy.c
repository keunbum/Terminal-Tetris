#include <stdio.h>
#include <unistd.h>
#include <locale.h>

#include "draw/cursor.h"

int test_gotoxy(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
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
        wgotoxy(4, 0);
    }
    return 0;
}
#include <stdio.h>

#include "debug/local_debug.h"
#include "game_manager/menu.h"
#include "util/util.h"

#define TITLE_MENU_TOTAL_OPTION_NUM (2)

void draw_menu_screen(void)
{
    static const char *OPTIONS_TEXT[] = { "start", "exit" };
    
    wprintf(L"TETRIS\n");
    forn(i, TITLE_MENU_TOTAL_OPTION_NUM)
    {
        if (i > 0)
        {
            wprintf(L"  ");
        }
        wprintf(L"%d) %s", i + 1, OPTIONS_TEXT[i]);
    }
    wprintf(L"\n");
}

int read_menu_option(void)
{
    int cmd;
    scanf("%d", &cmd);
    if (cmd == 1)
    {
        return MENU_CMD_START_GAME;
    }
    if (cmd == 2)
    {
        return MENU_CMD_EXIT_GAME;
    }
    return MENU_CMD_ERROR;
}
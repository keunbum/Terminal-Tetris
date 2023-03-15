#include <stdio.h>
#include <wchar.h>

#include "debug/debug.h"
#include "game/game_manager/menu.h"
#include "util/util.h"

#define TITLE_MENU_TOTAL_OPTION_NUM (2)
void draw_title_menu_screen(void)
{
    debug();
    static const char *TITLE_MENU_OPTIONS_TEXT[] = {"start", "exit"};

    wprintf(L"TETRIS\n");
    forn(i, TITLE_MENU_TOTAL_OPTION_NUM)
    {
        if (i > 0)
        {
            wprintf(L"  ");
        }
        wprintf(L"%d) %s", i + 1, TITLE_MENU_OPTIONS_TEXT[i]);
    }
    wprintf(L"\n");
}

int read_title_menu_option(void)
{
    debug();
    int cmd;
    scanf("%d", &cmd);
    int ret = TITLE_MENU_CMD_ERROR;
    switch (cmd)
    {
    case 1:
        ret = TITLE_MENU_CMD_START_GAME;
        break;
    case 2:
        ret = TITLE_MENU_CMD_EXIT_GAME;
        break;
    default:
        break;
    }
    return ret;
}
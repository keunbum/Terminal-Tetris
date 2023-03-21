#include <stdbool.h>
#include <stdio.h>
#include <wchar.h>

#include "debug/debug.h"
#include "draw_tool/cursor.h"
#include "error/error_handling.h"
#include "game/menu/game_selection_menu.h"
#include "game/menu/title_menu.h"

static void draw_title_menu_screen(void)
{
    debug();

    static const char* S_TITLE_MENU_OPTIONS_TEXT[] = { "select games", "exit" };
    static const int S_TITLE_MENU_TOTAL_OPTION_NUM = (int)(sizeof(S_TITLE_MENU_OPTIONS_TEXT) / sizeof(S_TITLE_MENU_OPTIONS_TEXT[0]));

    wclear();
    wprintf(L"TETRIS GAME\n");
    for (int i = 0; i < S_TITLE_MENU_TOTAL_OPTION_NUM; ++i) {
        if (i > 0) {
            wprintf(L"  ");
        }
        wprintf(L"%d) %s", i + 1, S_TITLE_MENU_OPTIONS_TEXT[i]);
    }
    wprintf(L"\n");
}

static int read_title_menu_option(void)
{
    debug();

    int cmd;
    scanf("%d", &cmd);
    int ret = TITLE_MENU_CMD_ERROR;
    switch (cmd) {
    case 1:
        ret = TITLE_MENU_CMD_RUN_GAME_SELECTION_MENU;
        break;
    case 2:
        ret = TITLE_MENU_CMD_EXIT_GAME;
        break;
    default:
        handle_error("read_title_menu_option() error");
        break;
    }
    return ret;
}

static void exit_title_menu(void)
{
    debug();

    /* It might need some cleanup module later. */
}

static void handle_title_menu_cmd(int cmd)
{
    debug();

    switch (cmd) {
    case TITLE_MENU_CMD_RUN_GAME_SELECTION_MENU:
        run_game_selection_menu();
        break;
    case TITLE_MENU_CMD_EXIT_GAME:
        exit_title_menu();
        break;
    case TITLE_MENU_CMD_ERROR:
        handle_error("Reading input failed.");
        break;
    default:
        /* do nothing */
        break;
    }
}

void run_title_menu(void)
{
    debug();

    /* Right now it's accepting options in scanf format,
       but in the future I'd like to be able to navigate through the options with the arrow keys.
       It would be better to run separate modules for drawing on the screen and receiving input. */
    while (true) {
        draw_title_menu_screen();
        int cmd = read_title_menu_option();
        handle_title_menu_cmd(cmd);
        if (cmd == TITLE_MENU_CMD_EXIT_GAME) {
            break;
        }
    }
}
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <wchar.h>

#include "debug.h"
#include "draw/draw_tool.h"
#include "error_handling.h"
#include "game_selection_menu.h"
#include "title_menu.h"

static void draw_title_menu_screen(void)
{
    static const char* S_TITLE_MENU_OPTIONS_TEXT[] = { "select games", "exit" };
    static const int S_TITLE_MENU_TOTAL_OPTION_NUM = (int)(sizeof(S_TITLE_MENU_OPTIONS_TEXT) / sizeof(S_TITLE_MENU_OPTIONS_TEXT[0]));
    static const wchar_t* S_TITLE[6] = {
        L".___________. _______ .___________..______       __       _______.",
        L"|           ||   ____||           ||   _  \\     |  |     /       |",
        L"`---|  |----`|  |__   `---|  |----`|  |_)  |    |  |    |   (----\\",
        L"    |  |     |   __|      |  |     |      /     |  |     \\   \\    ",
        L"    |  |     |  |____     |  |     |  |\\  \\----.|  | .----)   |   ",
        L"    |__|     |_______|    |__|     | _| `._____||__| |_______/    "
    };

    wclear();
    wdraw_rows_newline_at_each(6, S_TITLE, 0, 0);
    wdraw_newline();
    for (int i = 0; i < S_TITLE_MENU_TOTAL_OPTION_NUM; ++i) {
        if (i > 0) {
            fputws(L"  ", stdout);
        }
        wprintf(L"%d) %s", i + 1, S_TITLE_MENU_OPTIONS_TEXT[i]);
    }
    wdraw_newline();
}

static title_menu_cmd_t read_title_menu_option(void)
{
    int cmd;
    title_menu_cmd_t ret;
    if (scanf("%d", &cmd) != 1) {
        ret = TITLE_MENU_CMD_INVAL;
        goto return_line;
    }
    switch (cmd) {
    case 1:
        ret = TITLE_MENU_CMD_RUN_GAME_SELECTION_MENU;
        break;
    case 2:
        ret = TITLE_MENU_CMD_EXIT_GAME;
        break;
    default:
        ret = TITLE_MENU_CMD_INVAL;
        break;
    }
return_line:
    return ret;
}

static void exit_title_menu(void)
{
    /* It might need some cleanup module later. */
}

static void handle_title_menu_cmd(title_menu_cmd_t cmd)
{
    switch (cmd) {
    case TITLE_MENU_CMD_RUN_GAME_SELECTION_MENU:
        run_game_selection_menu();
        break;
    case TITLE_MENU_CMD_EXIT_GAME:
        exit_title_menu();
        break;
    case TITLE_MENU_CMD_INVAL:
        assert(false);
        break;
    }
}

void run_title_menu(void)
{
    /* Right now it's accepting options in scanf format,
       but I'd like to be able to navigate through the options with the arrow keys later.
       It would be better to run separate modules for drawing on the screen and receiving input. */
    while (true) {
        draw_title_menu_screen();
        title_menu_cmd_t cmd = read_title_menu_option();
        handle_title_menu_cmd(cmd);
        if (cmd == TITLE_MENU_CMD_EXIT_GAME) {
            break;
        }
    }
}
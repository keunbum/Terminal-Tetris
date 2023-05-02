#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <wchar.h>

#include "debug.h"
#include "draw/draw_tool.h"
#include "error_handling.h"
#include "game_selection_menu.h"
#include "game_system_manager.h"
#include "tetris/play/tetris_play_manager_single.h"

#define GAME_SYSTEM_MODULE_NUM (1)

static const game_system_module_t GS_GAME_OBJECTS[GAME_SYSTEM_MODULE_NUM] = {
    {
        .name = "basic tetris",
        .module = run_tetris_play_single_mode,
        .module_arg = NULL,
    },
};

static const char* GS_GAME_SELECTION_MENU_OPTIONS_TEXT[] = { GS_GAME_OBJECTS[0].name, "back" };
static const int GS_GAME_SELECTION_MENU_TOTAL_OPTION_NUM = (int)(sizeof(GS_GAME_SELECTION_MENU_OPTIONS_TEXT) / sizeof(GS_GAME_SELECTION_MENU_OPTIONS_TEXT[0]));

static void draw_game_selection_menu_screen(void)
{
    static const wchar_t* S_TITLE[] = {
        L" __  __      __  __ ___    __             __ ",
        L"(_  |_  |   |_  /    |    / _   /\\  |\\/| |_  ",
        L"__) |__ |__ |__ \\__  |    \\__) /--\\ |  | |__ "
    };
    wclear();
    wdraw_rows_newline_at_each(3, S_TITLE, 0, 0);
    wdraw_newline();
    for (int i = 0; i < GS_GAME_SELECTION_MENU_TOTAL_OPTION_NUM; ++i) {
        if (i > 0) {
            fputws(L"  ", stdout);
        }
        wprintf(L"%d) %s", i + 1, GS_GAME_SELECTION_MENU_OPTIONS_TEXT[i]);
    }
    wdraw_newline();
}

static game_selection_menu_cmd_t read_game_selection_menu_option(void)
{
    game_selection_menu_cmd_t cmd;
    int res = scanf("%d", &cmd);
    (void)res;
    return cmd;
}

static void cleanup_game_selection_menu(void)
{
    /* It might need some cleanup module later. */
}

static inline int cmd_to_gamenum(int cmd)
{
    return cmd - 1;
}

/*
 * if exit: return false;
 * else return true;
 */
static bool handle_game_selection_menu_cmd(game_selection_menu_cmd_t cmd)
{
    if (cmd == GAME_SELECTION_MENU_CMD_INVAL) {
        handle_error("Reading input failed.");
    }
    if (cmd == GS_GAME_SELECTION_MENU_TOTAL_OPTION_NUM) {
        cleanup_game_selection_menu();
        return false;
    }
    if (1 <= cmd && cmd <= GS_GAME_SELECTION_MENU_TOTAL_OPTION_NUM - 1) {
        const game_system_module_t* game = GS_GAME_OBJECTS + cmd_to_gamenum((int)cmd);
        game->module(game->module_arg);
        return true;
    }
    return true;
}

void run_game_selection_menu(void)
{
    game_selection_menu_cmd_t cmd;
    do {
        draw_game_selection_menu_screen();
        cmd = read_game_selection_menu_option();
    } while (handle_game_selection_menu_cmd(cmd));
}
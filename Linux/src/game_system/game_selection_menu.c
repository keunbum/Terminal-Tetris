#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <wchar.h>

#include "debug.h"
#include "draw/cursor.h"
#include "error_handling.h"
#include "game_selection_menu.h"
#include "tetris/play/tetris_play_single_manager.h"
#include "game_system_manager.h"

static const game_module_t G_S_GAME_OBJECTS[1] = {
    {
        .name = "basic tetris",
        .module = run_tetris_play_single_mode,
        .module_arg = NULL,
    },
};

static const char* G_S_GAME_SELECTION_MENU_OPTIONS_TEXT[] = { G_S_GAME_OBJECTS[0].name, "back" };

static const int G_S_GAME_SELECTION_MENU_TOTAL_OPTION_NUM = (int)(sizeof(G_S_GAME_SELECTION_MENU_OPTIONS_TEXT) / sizeof(G_S_GAME_SELECTION_MENU_OPTIONS_TEXT[0]));

static void draw_game_selection_menu_screen(void)
{
    debug();

    wclear();
    wprintf(L"SELECT GAME\n");
    for (int i = 0; i < G_S_GAME_SELECTION_MENU_TOTAL_OPTION_NUM; ++i) {
        if (i > 0) {
            wprintf(L"  ");
        }
        wprintf(L"%d) %s", i + 1, G_S_GAME_SELECTION_MENU_OPTIONS_TEXT[i]);
    }
    wprintf(L"\n");
}

static int read_game_selection_menu_option(void)
{
    debug();

    int cmd;
    scanf("%d", &cmd);
    return cmd;
}

static void cleanup_game_selection_menu(void)
{
    debug();

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
static bool handle_game_selection_menu_cmd(int cmd)
{
    debug();

    if (cmd == GAME_SELECTION_MENU_CMD_INVAL) {
        handle_error("Reading input failed.");
    }
    if (cmd == G_S_GAME_SELECTION_MENU_TOTAL_OPTION_NUM) {
        cleanup_game_selection_menu();
        return false;
    }
    if (1 <= cmd && cmd <= G_S_GAME_SELECTION_MENU_TOTAL_OPTION_NUM - 1) {
        const game_module_t* g = G_S_GAME_OBJECTS + cmd_to_gamenum(cmd);
        g->module(g->module_arg);
        return true;
    }
    return true;
}

void run_game_selection_menu(void)
{
    debug();

    int cmd;
    do {
        draw_game_selection_menu_screen();
        cmd = read_game_selection_menu_option();
    } while (handle_game_selection_menu_cmd(cmd));
}
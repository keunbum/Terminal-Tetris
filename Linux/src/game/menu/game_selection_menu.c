#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#include "debug/debug.h"
#include "error/error_handling.h"
#include "game/menu/game_selection_menu.h"
#include "game/game_play/mode/single/single_play_manager.h"
#include "game/game_play/game_object/game_object.h"
#include "util/util.h"

static const game_object_t G_S_GAME_OBJECTS[] = {
    {
        "basic tetris",
        run_single_mode
    }
};

static const char *G_S_GAME_SELECTION_MENU_OPTIONS_TEXT[] = {G_S_GAME_OBJECTS[0].name, "exit"};

static const int G_S_GAME_SELECTION_MENU_TOTAL_OPTION_NUM =
    (int) (sizeof(G_S_GAME_SELECTION_MENU_OPTIONS_TEXT) / sizeof(G_S_GAME_SELECTION_MENU_OPTIONS_TEXT[0]));

static void draw_game_selection_menu_screen(void)
{
    debug();

    wprintf(L"SELECT GAME\n");
    forn (i, G_S_GAME_SELECTION_MENU_TOTAL_OPTION_NUM) {
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

static int cmd_to_gamenum(int cmd) {
    return cmd - 1;
}

static bool handle_game_selection_menu_cmd(int cmd)
{
    debug();

    if (cmd == GAME_SELECTION_MENU_CMD_ERROR)
    {
        handle_error("Reading input failed.");
    }
    if (cmd == G_S_GAME_SELECTION_MENU_TOTAL_OPTION_NUM)
    {
        cleanup_game_selection_menu();
        return false;
    }
    if (1 <= cmd && cmd <= G_S_GAME_SELECTION_MENU_TOTAL_OPTION_NUM - 1)
    {
        G_S_GAME_OBJECTS[cmd_to_gamenum(cmd)].module(NULL);
        return true;
    }
    return true;
}

void run_game_selection_menu(void)
{
    int cmd;
    draw_game_selection_menu_screen();
    do
    {
        cmd = read_game_selection_menu_option();
    } while (handle_game_selection_menu_cmd(cmd));
}
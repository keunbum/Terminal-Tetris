#include "debug/debug.h"
#include "game/menu/title_menu.h"
#include "game_manager.h"

void run_game_manager(void)
{
    debug();

    run_title_menu();
}
#include "debug.h"
#include "game_system/menu/title_menu.h"
#include "game_system_manager.h"

void run_game_manager(void)
{
    debug();

    run_title_menu();
}
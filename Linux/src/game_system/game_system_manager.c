#include <stdlib.h>

#include "debug.h"
#include "draw/cursor.h"
#include "game_system_manager.h"
#include "localize/localize.h"
#include "mt19937.h"
#include "tetris/scene/tetris_play_scene.h"
#include "title_menu.h"

static void init_game_system(void)
{
    localize();
    init_cursor_lock();
    mt19937_srand((uint32_t)time(NULL));
}

static void cleanup_game_system(void)
{
    cleanup_cursor_lock();
    cleanup_tetris_play_scene();
}

void exit_cleanup_game_system(int status)
{
    cleanup_game_system();
    exit(status);
}

void run_game_system_manager(void)
{
    init_game_system();
    run_title_menu();
    cleanup_game_system();
}
#include <stdlib.h>

#include "game_system_manager.h"
#include "debug.h"
#include "draw/cursor.h"
#include "localize/localize.h"
#include "menu/title_menu.h"
#include "mt19937.h"
#include "tetris/play/tetris_play_board.h"
#include "tetris/tetromino/tetromino.h"

static void init_game_system(void)
{
    debug();

    localize();

    init_cursor_lock();
    init_tetris_play_tetromino_lock();
    init_tetris_play_board_lock();

    init_mt19937((uint32_t)time(NULL));
}

static void cleanup_game_system(void)
{
    debug();

    cleanup_tetris_play_board_lock();
    cleanup_tetris_play_update_lock();
    cleanup_cursor_lock();
}

void exit_cleanup_game_system(int status)
{
    cleanup_game_system();
    exit(status);
}

void run_game_system_manager(void)
{
    debug();

    init_game_system();
    run_title_menu();
    cleanup_game_system();

}
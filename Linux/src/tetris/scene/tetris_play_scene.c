#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "draw/draw_tool.h"
#include "error_handling.h"
#include "tetris/tetris_play_manager.h"

static void draw_tetris_play_single_default_scene(const tetris_play_manager_t* play_manager)
{
    debug();

    my_assert(play_manager != NULL);

    wdraw_screen(&play_manager->screen);
    wdraw_board(&play_manager->board);
    wdraw_tetris_play_statistics(&play_manager->stat, get_block_wprint_set(&play_manager->tetro_man.tetro_gen));
    wdraw_tetromino_manager_queue(&play_manager->tetro_man);
    fflush(stdout);
}

void load_tetris_play_scene(const tetris_play_manager_t* play_manager)
{
    debug();

    wclear();
    wdisable_cursor();

    switch (play_manager->play_mode) {
    case TETRIS_PLAY_MODE_SINGLE:
        draw_tetris_play_single_default_scene(play_manager);
        break;
    case TETRIS_PLAY_MODE_MULTI:
        /* intentional fallthrough */
    default:
        handle_error("load_tetris_play_scene() Not a valid game play_mode");
        break;
    }
}

void cleanup_tetris_play_scene(void)
{
    debug();

    wenable_cursor();
    wclear();
}

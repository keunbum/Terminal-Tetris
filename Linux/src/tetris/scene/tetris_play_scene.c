#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "draw/draw_tool.h"
#include "error_handling.h"
#include "tetris/play/tetris_play_manager.h"

static void draw_tetris_play_single_default_scene(const tetris_play_manager_t* play_manager)
{
    wdraw_frame(&play_manager->screen_frame, 0);
    wdraw_board(&play_manager->tetro_man.board);
    wdraw_tetromino_manager(&play_manager->tetro_man);
    {
        int _ = 0;
        game_time_t __ = 1.0f;
        wdraw_fps(&_, &__);
    }
    wdraw_show_manual(play_manager, TETRIS_PLAY_MANUAL_KEYBOARD);
    fflush(stdout);
}

void load_tetris_play_scene(const tetris_play_manager_t* play_manager)
{
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
    wenable_cursor();
    wclear();
}

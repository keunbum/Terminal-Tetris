#include "debug.h"
#include "screen.h"
#include "tetris/scene/tetris_play_scene.h"

void wdraw_screen(const screen_t* screen)
{
    debug();

    my_assert(screen != NULL);

    cursor_lock();
    wdraw_boundary_at_with(UNIT_MATRIX_HOR_LINE_THIN,
        UNIT_MATRIX_VER_LINE_THIN,
        TETRIS_PLAY_SINGLE_SCREEN_HEIGHT_WPRINT,
        TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT,
        (int)screen->pos.x, (int)screen->pos.y,
        UNIT_MATRIX_CORNER_TOP_LEFT_THIN,
        UNIT_MATRIX_CORNER_TOP_RIGHT_THIN,
        UNIT_MATRIX_CORNER_BOT_LEFT_THIN,
        UNIT_MATRIX_CORNER_BOT_RIGHT_THIN);
    cursor_unlock();
}
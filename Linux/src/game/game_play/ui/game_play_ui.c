#include <stdio.h>

#include "debug/debug.h"
#include "game/draw_tool/cursor.h"
#include "game/draw_tool/draw_tool.h"
#include "game/game_play/ui/game_play_screen.h"
#include "game/game_play/ui/game_play_grid_matrix.h"
#include "util/util.h"

static void draw_outside_area_at(int sx, int sy)
{
    draw_boundary_at_with(UNIT_MATRIX_HOR_LINE_THIN, UNIT_MATRIX_VER_LINE_THIN, GAME_PLAY_SCREEN_HEIGHT, GAME_PLAY_SCREEN_WIDTH, sx, sy,
        UNIT_MATRIX_CORNER_TOP_LEFT_THIN,
        UNIT_MATRIX_CORNER_TOP_RIGHT_THIN,
        UNIT_MATRIX_CORNER_BOT_LEFT_THIN,
        UNIT_MATRIX_CORNER_BOT_RIGHT_THIN
    );
}

static void draw_inside_area_at(int sx, int sy)
{
    draw_boundary_at(UNIT_MATRIX_HOR_LINE, UNIT_MATRIX_VER_LINE, GAME_PLAY_GRID_MATRIX_HEIGHT, GAME_PLAY_GRID_MATRIX_WIDTH, sx, sy);
    int small_h = GAME_PLAY_GRID_MATRIX_HEIGHT - 2;
    int small_w = GAME_PLAY_GRID_MATRIX_WIDTH - 2;
    wgotoxy(sx + 1, sy + 1);
    forn (i, small_h) {
        draw_row_matrix_at(BLOCK_EMPTY, sx + 1 + i, sy + 1, sy + 1 + small_w / 2);
    }
}

static void draw_game_play_single_outside_area_at(int sx, int sy)
{
    draw_outside_area_at(sx, sy);
}

static void draw_game_play_single_inside_area_at(int sx, int sy)
{
    draw_inside_area_at(sx, sy);
}

static void draw_game_play_single_whole_screen_at(int sx, int sy)
{
    debug();

    wclear();
    //wdisable_cursor();
    draw_game_play_single_outside_area_at(sx, sy);
    draw_game_play_single_inside_area_at(sx + GAME_PLAY_GRID_MATRIX_START_POS_X, sy + GAME_PLAY_GRID_MATRIX_START_POS_Y);
}

void load_game_play_single_ui(int screen_start_pos_x, int screen_start_pos_y, int screen_height)
{
    debug();

    draw_game_play_single_whole_screen_at(screen_start_pos_x, screen_start_pos_y);
    // draw_a_default_tetromino_at(0, 20, 20);
    fflush(stdout);
    wgotoxy(screen_start_pos_x + screen_height + 1, 0);
}

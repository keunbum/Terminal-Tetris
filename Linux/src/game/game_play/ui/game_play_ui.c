#include <stdio.h>

#include "debug/debug.h"
#include "error/error_handling.h"
#include "draw_tool/cursor.h"
#include "draw_tool/draw_tool.h"
#include "game/game_play/tetromino/block.h"
#include "game/game_play/ui/game_play_grid_matrix.h"
#include "game/game_play/ui/game_play_screen.h"
#include "game/game_play/ui/game_play_ui.h"


static void draw_game_play_outside_area_at(int sx, int sy)
{
    draw_boundary_at_with(UNIT_MATRIX_HOR_LINE_THIN, UNIT_MATRIX_VER_LINE_THIN, GAME_PLAY_SCREEN_HEIGHT, GAME_PLAY_SCREEN_WIDTH, sx, sy,
        UNIT_MATRIX_CORNER_TOP_LEFT_THIN,
        UNIT_MATRIX_CORNER_TOP_RIGHT_THIN,
        UNIT_MATRIX_CORNER_BOT_LEFT_THIN,
        UNIT_MATRIX_CORNER_BOT_RIGHT_THIN);
}

/*
static void old_draw_game_play_inside_area_at(int topleft_pos_x, int topleft_pos_y)
{
    const int small_h = GAME_PLAY_GRID_MATRIX_HEIGHT - 2;
    const int small_w = GAME_PLAY_GRID_MATRIX_WIDTH - 2;

    wgotoxy(topleft_pos_x, topleft_pos_y);
    draw_boundary_at(UNIT_MATRIX_HOR_LINE, UNIT_MATRIX_VER_LINE, GAME_PLAY_GRID_MATRIX_HEIGHT, GAME_PLAY_GRID_MATRIX_WIDTH, topleft_pos_x, topleft_pos_y);
    wgotoxy(topleft_pos_x + 1, topleft_pos_y + 1);
    for (int i = 0; i < small_h; ++i) {
        draw_row_matrix_at(BLOCK_EMPTY, topleft_pos_x + 1 + i, topleft_pos_y + 1, topleft_pos_y + 1 + small_w / 2);
    }
}*/

static void draw_game_play_inside_area_at(int topleft_pos_x, int topleft_pos_y)
{
    static wchar_t S_TOP_LINE[2 * NEW_GAME_PLAY_GRID_MATRIX_WIDTH + 1];
    static wchar_t S_MID_LINE[NEW_GAME_PLAY_GRID_MATRIX_WIDTH + 1];
    static wchar_t S_BOT_LINE[2 * NEW_GAME_PLAY_GRID_MATRIX_WIDTH + 1];

    const int topbot_correction = -2;
    set_row_line(S_TOP_LINE, 2 * NEW_GAME_PLAY_GRID_MATRIX_WIDTH + topbot_correction, UNIT_MATRIX_CORNER_TOP_LEFT, UNIT_MATRIX_HOR_LINE, UNIT_MATRIX_CORNER_TOP_RIGHT);
    set_row_line(S_MID_LINE, NEW_GAME_PLAY_GRID_MATRIX_WIDTH, UNIT_MATRIX_VER_LINE, BLOCK_EMPTY, UNIT_MATRIX_VER_LINE);
    set_row_line(S_BOT_LINE, 2 * NEW_GAME_PLAY_GRID_MATRIX_WIDTH + topbot_correction, UNIT_MATRIX_CORNER_BOT_LEFT, UNIT_MATRIX_HOR_LINE, UNIT_MATRIX_CORNER_BOT_RIGHT);

    wgotoxy(topleft_pos_x, topleft_pos_y);
    const int cursor_move_length = 2 * (NEW_GAME_PLAY_GRID_MATRIX_WIDTH - 1);
    draw_row_cursor_newline(S_TOP_LINE, cursor_move_length);
    for (int i = 0; i < GAME_PLAY_GRID_MATRIX_HEIGHT - 2; ++i) {
        draw_row_cursor_newline(S_MID_LINE, cursor_move_length);
    }
    draw_row_cursor_newline(S_BOT_LINE, cursor_move_length);
}

static void draw_game_play_single_outside_area_at(int sx, int sy)
{
    draw_game_play_outside_area_at(sx, sy);
}

static void draw_game_play_single_whole_screen_at(int sx, int sy)
{
    debug();

    // wdisable_cursor();
    draw_game_play_single_outside_area_at(sx, sy);
    draw_game_play_inside_area_at(sx + GAME_PLAY_GRID_MATRIX_START_POS_X, sy + GAME_PLAY_GRID_MATRIX_START_POS_Y);
}

void set_row_line(wchar_t* const buf, int length, wchar_t beg, wchar_t mid, wchar_t end)
{
    buf[0] = beg;
    wmemset(buf + 1, mid, length - 2);
    buf[length - 1] = end;
    buf[length] = L'\0';
}

int load_game_play_ui(int game_mode, int screen_start_pos_x, int screen_start_pos_y, int screen_height)
{
    debug();

    wclear();

    int res = -1;
    switch (game_mode) {
    case GAME_PLAY_MODE_SINGLE:
        draw_game_play_single_whole_screen_at(screen_start_pos_x, screen_start_pos_y);
        res = 0;
        break;
    /* Multiplayer mode is not yet developed. */
    // case GAME_PLAY_MODE_MULTI:
    //     break;
    default:
        handle_error("Not a valid game mode");
        break;
    }
    fflush(stdout);
    wgotoxy(screen_start_pos_x + screen_height + 1, 0);
    return res;
}

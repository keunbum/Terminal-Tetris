#include <stdio.h>

#include "debug.h"
#include "draw/cursor.h"
#include "draw/draw_tool.h"
#include "error_handling.h"
#include "game_play_screen.h"
#include "tetris/physics/game_play_board_frame.h"
#include "tetris/scene/game_play_scene.h"
#include "tetris/tetromino/block.h"

static void draw_game_play_outside_area_at_r(int sx, int sy)
{
    debug();

    // pthread_mutex_lock(&g_cursor_mutex);
    wdraw_boundary_at_with(UNIT_MATRIX_HOR_LINE_THIN, UNIT_MATRIX_VER_LINE_THIN, GAME_PLAY_SINGLE_SCREEN_HEIGHT_WPRINT, GAME_PLAY_SINGLE_SCREEN_WIDTH_WPRINT, sx, sy,
        UNIT_MATRIX_CORNER_TOP_LEFT_THIN,
        UNIT_MATRIX_CORNER_TOP_RIGHT_THIN,
        UNIT_MATRIX_CORNER_BOT_LEFT_THIN,
        UNIT_MATRIX_CORNER_BOT_RIGHT_THIN);
    // pthread_mutex_unlock(&g_cursor_mutex);
}

static void wdraw_game_play_inside_area_at_r(int topleft_pos_x, int topleft_pos_y)
{
    debug();

    static wchar_t S_TOP_LINE[GAME_PLAY_BOARD_FRAME_WIDTH + 1];
    static wchar_t S_MID_LINE[GAME_PLAY_BOARD_FRAME_WIDTH + 1];
    static wchar_t S_BOT_LINE[GAME_PLAY_BOARD_FRAME_WIDTH + 1];

    const int topbot_correction = 0;
    const wchar_t game_board_unit_matrix_corner_top_left = L'\U0001f532';
    const wchar_t game_board_unit_matrix_corner_top_right = L'\U0001f532';
    const wchar_t game_board_unit_matrix_corner_bot_left = L'\U0001f532';
    const wchar_t game_board_unit_matrix_corner_bot_right = L'\U0001f532';
    const wchar_t game_board_unit_matrix_ver_line = L'\U0001f532';
    const wchar_t game_board_unit_matrix_hor_line = L'\U0001f532';

    wset_row_line(S_TOP_LINE, GAME_PLAY_BOARD_FRAME_WIDTH + topbot_correction, game_board_unit_matrix_corner_top_left, game_board_unit_matrix_hor_line, game_board_unit_matrix_corner_top_right);
    wset_row_line(S_MID_LINE, GAME_PLAY_BOARD_FRAME_WIDTH, game_board_unit_matrix_ver_line, BLOCK_WHITE_LARGE_SQUARE_WPRINT, game_board_unit_matrix_ver_line);
    wset_row_line(S_BOT_LINE, GAME_PLAY_BOARD_FRAME_WIDTH + topbot_correction, game_board_unit_matrix_corner_bot_left, game_board_unit_matrix_hor_line, game_board_unit_matrix_corner_bot_right);

    pthread_mutex_lock(&g_cursor_mtx);
    wgotoxy(topleft_pos_x, topleft_pos_y);
    const int cursor_move_length = 2 * GAME_PLAY_BOARD_FRAME_WIDTH;
    wdraw_row_newline(S_TOP_LINE, cursor_move_length);
    for (int i = 0; i < GAME_PLAY_BOARD_HEIGHT; ++i) {
        wdraw_row_newline(S_MID_LINE, cursor_move_length);
    }
    wdraw_row_newline(S_BOT_LINE, cursor_move_length);
    pthread_mutex_unlock(&g_cursor_mtx);
}

static void draw_game_play_single_outside_area_at_r(int sx, int sy)
{
    debug();

    draw_game_play_outside_area_at_r(sx, sy);
}

static void draw_game_play_single_whole_screen_at(int sx, int sy)
{
    debug();

    wdisable_cursor();

    draw_game_play_single_outside_area_at_r(sx, sy);
    wdraw_game_play_inside_area_at_r(sx + GAME_PLAY_BOARD_FRAME_START_POS_X_WPRINT, sy + GAME_PLAY_BOARD_FRAME_START_POS_Y_WPRINT);
    fflush(stdout);
}

int load_game_play_scene(int game_mode, int screen_start_pos_x, int screen_start_pos_y)
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
    return res;
}

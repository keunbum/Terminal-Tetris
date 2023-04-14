#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "draw/draw_tool.h"
#include "error_handling.h"
// #include "tetris/object/board.h"
// #include "tetris/play/tetris_play_statistic.h"
#include "tetris/tetris_play_manager.h"
// #include "tetris_play_scene.h"
// #include "tetris_play_screen.h"

// static void draw_tetris_play_outside_area_at_r(int sx, int sy)
// {
//     // debug();

//     cursor_lock();
//     wdraw_boundary_at_with(UNIT_MATRIX_HOR_LINE_THIN, UNIT_MATRIX_VER_LINE_THIN, TETRIS_PLAY_SINGLE_SCREEN_HEIGHT_WPRINT, TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT, sx, sy,
//         UNIT_MATRIX_CORNER_TOP_LEFT_THIN,
//         UNIT_MATRIX_CORNER_TOP_RIGHT_THIN,
//         UNIT_MATRIX_CORNER_BOT_LEFT_THIN,
//         UNIT_MATRIX_CORNER_BOT_RIGHT_THIN);
//     cursor_unlock();
// }

// static void wdraw_tetris_play_inside_area_at_r(int topleft_pos_x, int topleft_pos_y)
// {
//     // debug();

//     static wchar_t S_TOP_LINE[BOARD_FRAME_WIDTH + 1];
//     static wchar_t S_MID_LINE[BOARD_FRAME_WIDTH + 1];
//     static wchar_t S_BOT_LINE[BOARD_FRAME_WIDTH + 1];

//     const wchar_t block_corner_top_left = BLOCK_WPRINT_BLACK_SQUARE_BUTTON;
//     const wchar_t block_corner_top_right = BLOCK_WPRINT_BLACK_SQUARE_BUTTON;
//     const wchar_t block_corner_bot_left = BLOCK_WPRINT_BLACK_SQUARE_BUTTON;
//     const wchar_t block_corner_bot_right = BLOCK_WPRINT_BLACK_SQUARE_BUTTON;
//     const wchar_t block_ver_line = BLOCK_WPRINT_BLACK_SQUARE_BUTTON;
//     const wchar_t block_hor_line = BLOCK_WPRINT_BLACK_SQUARE_BUTTON;
//     const wchar_t block_inner = BLOCK_WPRINT_WHITE_LARGE_SQUARE;

//     wset_row_line(S_TOP_LINE, BOARD_FRAME_WIDTH, block_corner_top_left, block_hor_line, block_corner_top_right);
//     wset_row_line(S_MID_LINE, BOARD_FRAME_WIDTH, block_ver_line, block_inner, block_ver_line);
//     wset_row_line(S_BOT_LINE, BOARD_FRAME_WIDTH, block_corner_bot_left, block_hor_line, block_corner_bot_right);

//     cursor_lock();
//     wgotoxy(topleft_pos_x, topleft_pos_y);
//     const int cursor_move_length = 2 * BOARD_FRAME_WIDTH;
//     wdraw_row_newline(S_TOP_LINE, cursor_move_length);
//     for (int i = 0; i < TETRIS_PLAY_BOARD_HEIGHT; ++i) {
//         wdraw_row_newline(S_MID_LINE, cursor_move_length);
//     }
//     wdraw_row_newline(S_BOT_LINE, cursor_move_length);
//     cursor_unlock();
// }

// static void draw_tetris_play_single_outside_area_at_r(int sx, int sy)
// {
//     // debug();

//     draw_tetris_play_outside_area_at_r(sx, sy);
// }

// static void draw_tetris_play_single_default_objects(int sx, int sy)
// {
//     // debug();

//     draw_tetris_play_single_outside_area_at_r(sx, sy);
//     wdraw_tetris_play_statistics_frame();
//     wdraw_tetris_play_inside_area_at_r(sx + BOARD_FRAME_POS_X_WPRINT, sy + BOARD_FRAME_POS_Y_WPRINT);
//     fflush(stdout);
// }

static void new_draw_tetris_play_single_default_scene(const tetris_play_manager_t* play_manager)
{
    debug();
    
    my_assert(play_manager != NULL);

    wdraw_screen(&play_manager->screen);
    wdraw_board(&play_manager->board);
    wdraw_tetris_play_statistics(&play_manager->stat, get_block_wprint_set(&play_manager->gen));
    fflush(stdout);
    exit(0);
}

// void load_tetris_play_scene(tetris_play_mode_t game_mode, int screen_start_pos_x, int screen_start_pos_y)
// {
//     debug();

//     wclear();
//     wdisable_cursor();

//     switch (game_mode) {
//     case TETRIS_PLAY_MODE_SINGLE:
//         draw_tetris_play_single_default_objects(screen_start_pos_x, screen_start_pos_y);
//         break;
//     case TETRIS_PLAY_MODE_MULTI:
//         /* intentional fallthrough */
//     default:
//         handle_error("load_tetris_play_scene() Not a valid game play_mode");
//         break;
//     }
// }

void new_load_tetris_play_scene(const tetris_play_manager_t* play_manager)
{
    debug();

    wclear();
    wdisable_cursor();

    switch (play_manager->play_mode) {
    case TETRIS_PLAY_MODE_SINGLE:
        new_draw_tetris_play_single_default_scene(play_manager);
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

#include "board.h"
#include "debug.h"
#include "draw/draw_tool.h"

board_lock_t g_board_lock;

void init_board(board_t* const board, board_grid_element_t val)
{
    debug();

    for (int i = 0; i < board->height; ++i) {
        for (int j = 0; j < board->width; ++j) {
            board->grid[i][j] = val;
        }
    }
    board->code_grid[0][0] = board->game_board_unit_matrix_corner_top_left;
    board->code_grid[0][board->width - 1] = board->game_board_unit_matrix_corner_top_right;
    board->code_grid[board->height - 1][0] = board->game_board_unit_matrix_corner_bot_left;
    board->code_grid[board->height - 1][board->width - 1] = board->game_board_unit_matrix_corner_bot_right;

    for (int i = 0; i < board->height; ++i) {
        if (i == 0 || i == board->height - 1) {
            for (int j = 1; j < board->width - 1; ++j) {
                board->code_grid[i][j] = board->game_board_unit_matrix_hor_line;
            }
            continue;
        }
        for (int j = 0; j < board->width; ++j) {
            if (j == 0 || j == board->width - 1) {
                board->code_grid[i][j] = board->game_board_unit_matrix_ver_line;
                continue;
            }
            board->code_grid[i][j] = board->game_board_unit_matrix_inner;
        }
    }
}

void wdraw_board(const board_t* board)
{
    // debug();
    // wchar_t TOP_LINE[board->frame_width + 1];
    // wchar_t MID_LINE[board->frame_width + 1];
    // wchar_t BOT_LINE[board->frame_width + 1];

    // const wchar_t game_board_unit_matrix_corner_top_left = BLOCK_WPRINT_BLACK_SQUARE_BUTTON;
    // const wchar_t game_board_unit_matrix_corner_top_right = BLOCK_WPRINT_BLACK_SQUARE_BUTTON;
    // const wchar_t game_board_unit_matrix_corner_bot_left = BLOCK_WPRINT_BLACK_SQUARE_BUTTON;
    // const wchar_t game_board_unit_matrix_corner_bot_right = BLOCK_WPRINT_BLACK_SQUARE_BUTTON;
    // const wchar_t game_board_unit_matrix_ver_line = BLOCK_WPRINT_BLACK_SQUARE_BUTTON;
    // const wchar_t game_board_unit_matrix_hor_line = BLOCK_WPRINT_BLACK_SQUARE_BUTTON;
    // const wchar_t game_board_unit_matrix_inner = BLOCK_WPRINT_WHITE_LARGE_SQUARE;

    // wset_row_line(TOP_LINE, board->frame_width, board->game_board_unit_matrix_corner_top_left, board->game_board_unit_matrix_hor_line, board->game_board_unit_matrix_corner_top_right);
    // wset_row_line(MID_LINE, board->frame_width, game_board_unit_matrix_ver_line, game_board_unit_matrix_inner, game_board_unit_matrix_ver_line);
    // wset_row_line(BOT_LINE, board->frame_width, game_board_unit_matrix_corner_bot_left, game_board_unit_matrix_hor_line, game_board_unit_matrix_corner_bot_right);

    // cursor_lock();
    // wgotoxy(topleft_pos_x, topleft_pos_y);
    // const int cursor_move_length = 2 * board->frame_width;
    // wdraw_row_newline(S_TOP_LINE, cursor_move_length);
    // for (int i = 0; i < TETRIS_PLAY_BOARD_HEIGHT; ++i) {
    //     wdraw_row_newline(S_MID_LINE, cursor_move_length);
    // }
    // wdraw_row_newline(S_BOT_LINE, cursor_move_length);
    // cursor_unlock();

    cursor_lock();
    wgotoxy((int)board->pos_wprint.x, (int)board->pos_wprint.y);
    for (int i = 0; i < board->height; ++i) {
        for (int j = 0; j < board->width; ++j) {
            wdraw_unit_matrix(board->code_grid[i][j]);
        }
        wprintf(L"\e[1B\e[%dD", board->width_wprint);
    }
    cursor_unlock();
}
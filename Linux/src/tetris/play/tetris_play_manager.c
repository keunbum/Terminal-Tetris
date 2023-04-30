#include <wchar.h>

#include "draw/cursor.h"
#include "tetris_play_manager.h"

#define MANUAL_ROWS (8)
#define MANUAL_COLS (2)
#define MAX_STR_LEN (32)

typedef const wchar_t* tetris_play_manual_row_t[MANUAL_COLS];

static void print_sub_wstr(int width, wchar_t inner, wchar_t edge)
{
    static wchar_t s_buf[MAX_STR_LEN];
    wmemset(s_buf + 0, inner, width - 1);
    s_buf[width - 1] = edge;
    s_buf[width] = L'\0';
    fputws(s_buf, stdout);
}

static void print_tetris_play_manual(int row, int col, const tetris_play_manual_row_t rows[MANUAL_ROWS], pos_int_t at)
{
    static const size_t S_UNIT_WIDTH = 13u;
    const int cursor_move_len = 1 + col * (S_UNIT_WIDTH + 1);
    wgotoxy(at.x, at.y);
    for (int i = 0; i < row + 1; ++i) {
        {
            fputwc(L'+', stdout);
            for (int j = 0; j < col; ++j) {
                print_sub_wstr(S_UNIT_WIDTH + 1, L'-', L'+');
            }
            wprintf(L"\e[1B\e[%dD", cursor_move_len);
        }
        if (i == row) {
            break;
        }
        {
            fputwc(L'|', stdout);
            for (int j = 0; j < col; ++j) {
                size_t slen = wcslen(rows[i][j]);
                size_t len_left = (S_UNIT_WIDTH - slen + 1) / 2;
                size_t len_right = S_UNIT_WIDTH - (slen + len_left);

                wprintf(L"%*ls", slen + len_left, rows[i][j]);

                print_sub_wstr(len_right + 1, L' ', L'|');
            }
            wprintf(L"\e[1B\e[%dD", cursor_move_len);
        }
    }
}

void wdraw_show_manual(const tetris_play_manager_t* play_manager, tetris_play_manual_t manual)
{
    static const wchar_t* S_MANUAL_TITLE[] = {
        L" __  __       ___  __   __     ",
        L"/   /  \\ |\\ |  |  |__) /  \\ |  ",
        L"\\__ \\__/ | \\|  |  | \\  \\__/ |__"
    };
    static const tetris_play_manual_row_t S_COLS[MANUAL_ROWS] = {
        { L"Move Left", L"←" },
        { L"Move Right", L"→" },
        { L"SOFT DROP", L"↓" },
        { L"HARD DROP", L"space bar" },
        { L"Rotate Right", L"↑ or X" },
        { L"Rotate Left", L"Z" },
        { L"HOLD", L"C" },
        { L"EXIT", L"Esc" },
    };
    pos_int_t pos_wprint = {
        play_manager->pos_wprint.x + 0,
        play_manager->pos_wprint.y + play_manager->screen_frame.width_wprint + 2
    };
    wdraw_rows_newline_at(3, S_MANUAL_TITLE, wcslen(S_MANUAL_TITLE[0]), pos_wprint.x, pos_wprint.y);
    pos_wprint.x += 4;
    switch (manual) {
    case TETRIS_PLAY_MANUAL_KEYBOARD:
        print_tetris_play_manual(MANUAL_ROWS, MANUAL_COLS, S_COLS, pos_wprint);
        break;
    case TETRIS_PLAY_MANUAL_CONTROLLER:
        break;
    }
}
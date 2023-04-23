#ifndef __DRAW_TOOL__H
#define __DRAW_TOOL__H

#include <stdbool.h>
#include <stdio.h>
#include <wchar.h>

#include "cursor.h"
#include "debug.h"

#define UNIT_MATRIX_CORNER_TOP_LEFT (0x2554)
#define UNIT_MATRIX_CORNER_TOP_RIGHT (0x2557)
#define UNIT_MATRIX_CORNER_BOT_LEFT (0x255A)
#define UNIT_MATRIX_CORNER_BOT_RIGHT (0x255D)

#define UNIT_MATRIX_CORNER_TOP_LEFT_THIN (0x250F)
#define UNIT_MATRIX_CORNER_TOP_RIGHT_THIN (0x2513)
#define UNIT_MATRIX_CORNER_BOT_LEFT_THIN (0x2517)
#define UNIT_MATRIX_CORNER_BOT_RIGHT_THIN (0x251B)

#define UNIT_MATRIX_HOR_LINE (0x2550)
#define UNIT_MATRIX_VER_LINE (0x2551)

#define UNIT_MATRIX_HOR_LINE_THIN (0x2501)
#define UNIT_MATRIX_VER_LINE_THIN (0x2503)

#define wprintf_at(x, y, ...) \
    do {                      \
        wgotoxy(x, y);        \
        wprintf(__VA_ARGS__); \
    } while (false)

#define wprintf_at_r(x, y, ...) \
    do {                        \
        cursor_lock();          \
        wgotoxy(x, y);          \
        wprintf(__VA_ARGS__);   \
        cursor_unlock();        \
    } while (false)

#define wdraw_newline() wprintf(L"\n")

static inline void wdraw_row_at(const wchar_t* wbuf, int pos_x_wprint, int pos_y_wprint)
{
    my_assert(wbuf != NULL);
    wgotoxy(pos_x_wprint, pos_y_wprint);
    wprintf(wbuf);
}

static inline void wdraw_row_newline(const wchar_t* wbuf, int cursor_move_width)
{
    // debug();
    my_assert(wbuf != NULL);
    wprintf(wbuf);
    wprintf(L"\e[1B\e[%dD", cursor_move_width);
}

static inline void wdraw_rows_newline_at(int height, const wchar_t** wbuf, int cursor_move_width, int pos_x_wprint, int pos_y_wprint)
{
    my_assert(wbuf != NULL);
    wgotoxy(pos_x_wprint, pos_y_wprint);
    for (int i = 0; i < height; ++i) {
        wdraw_row_newline(wbuf[i], cursor_move_width);
    }
    // wdraw_newline();
}

static inline void wdraw_rows_newline_at_r(int height, const wchar_t** wbuf, int cursor_move_width, int pos_x_wprint, int pos_y_wprint)
{
    cursor_lock();
    wdraw_rows_newline_at(height, wbuf, cursor_move_width, pos_x_wprint, pos_y_wprint);
    cursor_unlock();
}

static inline void wdraw_unit_matrix(wchar_t wch)
{
    putwc(wch, stdout);
}

static inline void wdraw_unit_matrix_at(wchar_t wch, int x, int y)
{
    wgotoxy(x, y);
    wdraw_unit_matrix(wch);
}

static inline void wdraw_unit_matrix_at_r(wchar_t wch, int x, int y)
{
    cursor_lock();
    wdraw_unit_matrix_at(wch, x, y);
    cursor_unlock();
}

void wdraw_boundary_at_with(wchar_t hor_block, wchar_t ver_block, int height, int width, int sx, int sy, wchar_t top_lft, wchar_t top_rgt, wchar_t bot_lft, wchar_t bot_rgt);
void wset_row_line(wchar_t* const buf, int length, wchar_t beg, wchar_t mid, wchar_t end);

#endif /* __DRAW_TOOL__H */
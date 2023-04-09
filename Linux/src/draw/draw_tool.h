#ifndef __DRAW_TOOL__H
#define __DRAW_TOOL__H

#include <stdbool.h>
#include <stdio.h>
#include <wchar.h>

#include "cursor.h"

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

static inline void wdraw_row_newline(const wchar_t* buf, int cursor_move_width)
{
    wprintf(buf);
    wprintf(L"\e[1B\e[%dD", cursor_move_width);
}

static inline void wdraw_rows_newline_at(int height, const wchar_t** buf, int cursor_move_width, int pos_x_wprint, int pos_y_wprint)
{
    wgotoxy(pos_x_wprint, pos_y_wprint);
    for (int i = 0; i < height; ++i) {
        wdraw_row_newline(buf[i], cursor_move_width);
    }
    wdraw_newline();
}

#define wdraw_rows_newline_at_r(...)        \
    do {                                    \
        cursor_lock();                      \
        wdraw_rows_newline_at(__VA_ARGS__); \
        cursor_unlock();                    \
    } while (false)

static inline void wdraw_unit_matrix(wchar_t wch)
{
    putwc(wch, stdout);
}

static inline void wdraw_unit_matrix_at(wchar_t ch, int x, int y)
{
    wgotoxy(x, y);
    wdraw_unit_matrix(ch);
}

void wdraw_row_matrix_at(wchar_t, int, int, int);
void wdraw_boundary_at_with(wchar_t, wchar_t, int, int, int, int, wchar_t, wchar_t, wchar_t, wchar_t);
void wdraw_boundary_at(wchar_t, wchar_t, int, int, int, int);
void wset_row_line(wchar_t* const, int, wchar_t, wchar_t, wchar_t);

#endif /* __DRAW_TOOL__H */
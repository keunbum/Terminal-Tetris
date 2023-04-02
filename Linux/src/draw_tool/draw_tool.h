#ifndef __DRAW_TOOL__H
#define __DRAW_TOOL__H

#include <stdbool.h>
#include <wchar.h>

#include "draw_tool/cursor.h"

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

#define wdraw_newline() wprintf(L"\n")
#define wdraw_row_newline(buf, cursor_move_width)   \
    do {                                            \
        wprintf(buf);                               \
        wprintf(L"\e[1B\e[%dD", cursor_move_width); \
    } while (false)
#define wdraw_rows_newline_at_r(height, buf, cursor_move_width, x, y) \
    do {                                                              \
        pthread_mutex_lock(&g_cursor_mutex);                          \
        wgotoxy(x, y);                                                \
        for (int i = 0; i < height; ++i) {                            \
            wdraw_row_newline(buf[i], cursor_move_width);             \
        }                                                             \
        wdraw_newline();                                              \
        pthread_mutex_unlock(&g_cursor_mutex);                        \
    } while (false)

void wdraw_unit_matrix(wchar_t);
void wdraw_row_matrix_at(wchar_t, int, int, int);
void wdraw_boundary_at_with(wchar_t, wchar_t, int, int, int, int, wchar_t, wchar_t, wchar_t, wchar_t);
void wdraw_boundary_at(wchar_t, wchar_t, int, int, int, int);

#endif /* __DRAW_TOOL__H */
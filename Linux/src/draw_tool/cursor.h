#ifndef __CURSOR__H
#define __CURSOR__H

#include <stdarg.h>
#include <wchar.h>

/* For all macro functions, it must be implemented as a wchar_t version. */

#define wclear() wprintf(L"\e[H\e[J")
#define wgotoxy(x, y) wprintf(L"\e[%d;%df", (x) + 1, (y) + 1)

#define wdisable_cursor() wprintf(L"\e[?25l")
#define wenable_cursor() wprintf(L"\e[?25h")

#define wmove_cursor_up_by(n) wprintf(L"\e[%dA", n)
#define wmove_cursor_down_by(n) wprintf(L"\e[%dB", n)
#define wmove_cursor_right_by(n) wprintf(L"\e[%dC", n)
#define wmove_cursor_left_by(n) wprintf(L"\e[%dD", n)
#define wmove_cursor_up() wmove_cursor_up_by(1)
#define wmove_cursor_down() wmove_cursor_down_by(1)
#define wmove_cursor_right() wmove_cursor_right_by(1)
#define wmove_cursor_left() wmove_cursor_left_by(1)

#define wprintf_at(x, y, ...) wgotoxy(x, y), wprintf(__VA_ARGS__)

#endif /* __CURSOR__H */

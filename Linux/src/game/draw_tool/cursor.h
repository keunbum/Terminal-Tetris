#ifndef __CURSOR__H
#define __CURSOR__H

#include <wchar.h>

/* For all macro functions, it must be implemented as a wchar_t version. */

#define wclear() wprintf(L"\e[H\e[J")
#define wgotoxy(x, y) wprintf(L"\e[%d;%df", (x) + 1, (y) + 1)

#define wdisable_cursor() wprintf(L"\e[?25l")
#define wenable_cursor() wprintf(L"\e[?25h")

/* need to be tested.
#define wmove_cursor_up() wprintf(L"\e[1a")
#define wmove_cursor_down() wprintf(L"\e[1b")
#define wmove_cursor_left() wprintf(L"\e[1c")
#define wmove_cursor_right() wprintf(L"\e[1d")
*/

#endif /* __CURSOR__H */

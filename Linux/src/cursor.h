#ifndef __CURSOR__H
#define __CURSOR__H

/*
 * For all macro functions, the wchat_t version must also be implemented.
 */

#define clear() printf("\033[H\033[J")
#define wclear() wprintf(L"\033[H\033[J")
// 0-based
#define gotoxy(x, y) printf("\e[%d;%df", (x) + 1, (y) + 1);
#define wgotoxy(x, y) wprintf(L"\e[%d;%df", (x) + 1, (y) + 1);

// It need to be tested.
/*
#define move_cursor_up() printf("\e[1a")
#define move_cursor_down() printf("\e[1b")
#define move_cursor_left() printf("\e[1c")
#define move_cursor_right() printf("\e[1d")
*/

#define disable_cursor() printf("\e[?25l")
#define enable_cursor() printf("\e[?25h")

#endif /* __CURSOR__H */


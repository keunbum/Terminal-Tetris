#ifndef __CURSOR__H
#define __CURSOR__H

#include <pthread.h>
#include <stdarg.h>
#include <stdbool.h>
#include <wchar.h>

#include "error_handling.h"

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

typedef pthread_spinlock_t cursor_lock_t;

extern cursor_lock_t g_cursor_lock;

#ifdef TETRIS_DEBUG
#define func_check_error(func, ...)               \
    do {                                          \
        int res;                                  \
        if ((res = func(__VA_ARGS__)) != 0) {     \
            handle_error_en(#func " error", res); \
        }                                         \
    } while (false)
#else
#define func_check_error(func, ...) \
    func(__VA_ARGS__)
#endif

#define init_cursor() func_check_error(pthread_spin_init, &g_cursor_lock, PTHREAD_PROCESS_PRIVATE)
#define cursor_lock() func_check_error(pthread_spin_lock, &g_cursor_lock)
#define cursor_unlock() func_check_error(pthread_spin_unlock, &g_cursor_lock)
#define cleanup_cursor() func_check_error(pthread_spin_destroy, &g_cursor_lock)

#endif /* __CURSOR__H */

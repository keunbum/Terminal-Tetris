#ifndef __CURSOR__H
#define __CURSOR__H

#include <pthread.h>
#include <stdarg.h>
#include <stdbool.h>
#include <wchar.h>

#include "debug.h"
#include "error_handling.h"
#include "pthread_macro.h"
#include "util.h"

/* For all macro functions, it must be implemented as a wchar_t version. */

#define wclear() wprintf(L"\e[H\e[J")
#define wdisable_cursor() wprintf(L"\e[?25l")
#define wenable_cursor() wprintf(L"\e[?25h")

static inline void wgotoxy(int x, int y)
{
    wprintf(L"\e[%d;%df", x + 1, y + 1);
}

static inline void wmove_cursor_up_by(int n)
{
    wprintf(L"\e[%dA", n);
}

static inline void wmove_cursor_down_by(int n)
{
    wprintf(L"\e[%dB", n);
}

static inline void wmove_cursor_right_by(int n)
{
    wprintf(L"\e[%dC", n);
}

static inline void wmove_cursor_left_by(int n)
{
    wprintf(L"\e[%dD", n);
}

#define wmove_cursor_up() wmove_cursor_up_by(1)
#define wmove_cursor_down() wmove_cursor_down_by(1)
#define wmove_cursor_right() wmove_cursor_right_by(1)
#define wmove_cursor_left() wmove_cursor_left_by(1)

typedef pthread_spinlock_t cursor_lock_t;

#define init_cursor_lock() func_check_error(pthread_spin_init, &g_cursor_lock, PTHREAD_PROCESS_PRIVATE)
#define cursor_lock() func_check_error(pthread_spin_lock, &g_cursor_lock)
#define cursor_unlock() func_check_error(pthread_spin_unlock, &g_cursor_lock)
#define cleanup_cursor_lock() func_check_error(pthread_spin_destroy, &g_cursor_lock)

// typedef pthread_mutex_t cursor_lock_t;
// #define init_cursor_lock() init_mutex_lock(g_cursor_lock)
// #define cursor_lock() check_mutex_lock(g_cursor_lock)
// #define cursor_unlock() check_mutex_unlock(g_cursor_lock)
// #define cleanup_cursor_lock() cleanup_mutex_lock(g_cursor_lock)

extern cursor_lock_t g_cursor_lock;

#endif /* __CURSOR__H */

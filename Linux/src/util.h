#ifndef __UTIL__H
#define __UTIL__H

#include <stdbool.h>

#include "error_handling.h"

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

#define max(x, y) ((x) > (y) ? (x) : (y))

#endif /* __UTIL__H */
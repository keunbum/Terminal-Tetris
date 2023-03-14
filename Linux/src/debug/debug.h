#ifndef __DEBUG__H
#define __DEBUG__H

#include <stdio.h>
#include <wchar.h>

#define LOCAL

#ifdef LOCAL
#define ewgotoxy(x, y) fwprintf(stderr, L"\e[%d;%df", (x) + 1, (y) + 1)
#define ewprintf(...) fwprintf(stderr, L ##__VA_ARGS__), fflush(stderr)
#include <assert.h>
#define my_assert(...) assert(__VA_ARGS__)
#else
#define ewgotoxy(x, y) (void) 0
#define ewprintf(...) void(0)
#define my_assert(...) (void) 0
#endif

#define debug() fwprintf(stderr, L"%s()\n", __func__)

#endif /* __DEBUG__H */
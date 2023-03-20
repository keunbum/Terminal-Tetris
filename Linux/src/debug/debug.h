#ifndef __DEBUG__H
#define __DEBUG__H

#ifdef DEBUG
#include <assert.h>
#include <stdio.h>
#include <wchar.h>

#define ewgotoxy(x, y) fwprintf(stderr, L"\e[%d;%df", (x) + 1, (y) + 1)
#define ewprintf(...) fwprintf(stderr, L##__VA_ARGS__), fflush(stderr)
#define my_assert(...) assert(__VA_ARGS__)
#define debug() fwprintf(stderr, L"%s()\n", __func__)
#else
#define ewgotoxy(x, y) (void)0
#define ewprintf(...) (void)0
#define my_assert(...) (void)0
#define debug() (void)0
#endif

#endif /* __DEBUG__H */
#ifndef __LOCAL_DEBUG__H
#define __LOCAL_DEBUG__H

#include <wchar.h>

#ifndef RELEASE
#define ewprintf(...) fwprintf(stderr, L ##__VA_ARGS__), fflush(stderr)
#include <assert.h>
#define Assert(...) assert(__VA_ARGS__)

#else

#define ewprintf(...) (void) 0
#define lassert(...) (void) 0

#endif


#endif /* __LOCAL_DEBUG__H */
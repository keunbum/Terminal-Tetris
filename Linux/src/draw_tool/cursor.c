#include <pthread.h>

#include "cursor.h"

pthread_mutex_t g_cursor_mutex = PTHREAD_MUTEX_INITIALIZER;
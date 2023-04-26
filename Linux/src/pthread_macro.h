#ifndef __PTHREAD_MACRO__H
#define __PTHREAD_MACRO__H

#include <pthread.h>

#include "util.h"

#define init_lock(lock) func_check_error(pthread_mutex_init, &lock, NULL)
#define check_lock(lock) func_check_error(pthread_mutex_lock, &lock)
#define check_unlock(lock) func_check_error(pthread_mutex_unlock, &lock)
#define cleanup_lock(lock) func_check_error(pthread_mutex_destroy, &lock)

#endif /* __PTHREAD_MACRO__H */
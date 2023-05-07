#ifndef __SIGNAL_MACRO__H
#define __SIGNAL_MACRO__H

#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "error_handling.h"

static inline void block_signal(int signum)
{
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, signum);
    int res = pthread_sigmask(SIG_BLOCK, &sigset, NULL);
    if (res == -1) {
        handle_error_en("pthread_sigmask() error", res);
    }
}

#endif /* __SIGNAL_MACRO__H */
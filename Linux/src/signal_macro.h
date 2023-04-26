#ifndef __SIGNAL_MACRO__H
#define __SIGNAL_MACRO__H

#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "error_handling.h"

/*
#define REGISTER_HANDLER_EMPTYSET(_act, _handler, _sa_flags, _sig_num, _oact) \
    do {                                                                      \
        _act.sa_handler = _handler;                                           \
        sigemptyset(&_act.sa_mask);                                           \
        _act.sa_flags = _sa_flags;                                            \
        if (sigaction(_sig_num, &_act, &o_act) == -1) {                       \
            handle_error("sigaction() error");                                \
        }                                                                     \
    } while (false)

#define REGISTER_HANDLER_EMPTYSET_NOOACT(_act, _handler, _sa_flags, _sig_num) \
    do {                                                                      \
        _act.sa_handler = _handler;                                           \
        sigemptyset(&_act.sa_mask);                                           \
        _act.sa_flags = _sa_flags;                                            \
        sigaction(_sig_num, &_act, 0);                                        \
    } while (false)
*/

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
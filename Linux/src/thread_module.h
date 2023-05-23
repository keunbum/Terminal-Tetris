#ifndef __THREAD_MODULE__H
#define __THREAD_MODULE__H

#include <pthread.h>
#include <stdbool.h>

#include "debug.h"
#include "error_handling.h"

typedef void* (*thread_module_func_t)(void* arg);

typedef struct {
    pthread_t thread_id;
    bool is_detached;
    thread_module_func_t main_func;
    void* main_func_arg;
    void* retval;
} thread_module_t;


void init_thread_module(thread_module_t* const out_module, bool is_detached, thread_module_func_t main_func, void* main_func_arg);
void cleanup_thread_module(thread_module_t* const out_module);
void run_thread_module(thread_module_t* const out_module);
void join_thread_module(thread_module_t* const out_module);

#endif /* __THREAD_MODULE__H */

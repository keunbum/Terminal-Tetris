#include "thread_module.h"

void init_thread_module(thread_module_t* const out_module,
    bool is_detached,
    thread_module_func_t main_func,
    void* main_func_arg)
{
    out_module->is_detached = is_detached;
    out_module->main_func = main_func;
    out_module->main_func_arg = main_func_arg;
    out_module->retval = NULL;
}

void cleanup_thread_module(thread_module_t* const out_module)
{
    out_module->retval = NULL;
}

void run_thread_module(thread_module_t* const out_module)
{
    int res = pthread_create(&out_module->thread_id, NULL, out_module->main_func, out_module->main_func_arg);
    if (res != 0) {
        handle_error_num("pthread_create() error", res);
    }
    if (out_module->is_detached) {
        res = pthread_detach(out_module->thread_id);
        if (res != 0) {
            handle_error_num("pthread_detach() error", res);
        }
    }
}

void join_thread_module(thread_module_t* const out_module)
{
    if (out_module->is_detached) {
        return;
    }
    if (pthread_join(out_module->thread_id, &out_module->retval) != 0) {
        handle_error("pthread_join() error");
    }
}
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
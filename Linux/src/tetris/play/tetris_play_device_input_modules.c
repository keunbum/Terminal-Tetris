#include <assert.h>
#include <stdbool.h>

#include "tetris_play_device_input_modules.h"
#include "tetris/tetris_play_manager.h"
#include "tetris_play_device_input_module_keyboard.h"
#include "tetris_play_device_input_module_controller.h"

#define THREAD_MODULE_NUM (2)

static void cleanup_device_input_modules(void* arg)
{
    thread_module_t* const modules = (thread_module_t*)arg;
    for (int i = 0; i < THREAD_MODULE_NUM; ++i) {
        int res = pthread_cancel(modules[i].thread_id);
        if (res != 0) {
            handle_error_en("pthread_cancel() error", res);
        }
    }
}

static void callback_cleanup_device_input_modules(void* arg)
{
    my_assert(arg != NULL);

    cleanup_device_input_modules(arg);
}

void* mainfunc_device_input_modules(void* arg)
{
    debug();

    static thread_module_t s_modules[THREAD_MODULE_NUM] = {
        {
            .is_detached = false,
            .main_func = mainfunc_device_input_module_keyboard,
            .retval = NULL,
        },
        {
            .is_detached = false,
            .main_func = mainfunc_device_input_controller,
            .retval = NULL,
        }
    };

    pthread_cleanup_push(callback_cleanup_device_input_modules, s_modules);

    for (int i = 0; i < THREAD_MODULE_NUM; ++i) {
        s_modules[i].main_func_arg = arg;
        run_thread_module_in_parallel(s_modules + i);
    }

    for (size_t i = 0; i < TETRIS_PLAY_SUBMODULE_NUM; ++i) {
        join_thread_module_in_parallel(s_modules + i);
    }

    cleanup_device_input_modules(s_modules);

    return NULL;
}
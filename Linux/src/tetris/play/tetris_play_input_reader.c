#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

#include "debug.h"
#include "tetris/tetris_play_manager.h"
#include "tetris_play_input_reader.h"
#include "tetris_play_update.h"

static void process_input_event(const struct input_event* ev, tetris_play_manager_t* const out_play_manager)
{
    (void)out_play_manager;

    if (ev->type == EV_KEY && ev->value == 1) {
        switch (ev->code) {
        case KEY_DOWN:
            try_move_tetromino(&out_play_manager->board, &out_play_manager->tetromino, DIR_BOT);
            break;
        case KEY_LEFT:
            try_move_tetromino(&out_play_manager->board, &out_play_manager->tetromino, DIR_LEFT);
            break;
        case KEY_RIGHT:
            try_move_tetromino(&out_play_manager->board, &out_play_manager->tetromino, DIR_RIGHT);
            break;
        case KEY_SPACE:
            /* Not yet implementted */
            // jump_tetromino(...);
            break;
        case KEY_Z:
            /* Not yet implementted */
            // try_rotate_tetromino_counterclockwise(...);
            break;
        case KEY_X:
            /* Not yet implementted */
            // try_rotate_tetromino_clockwise(...);
            break;
        case KEY_C:
            /* Not yet implementted */
            // maybe..
            // keep_tetromino(...);
            break;
        case KEY_ESC:
            /* Not a good logic */
            // A pause is ideal
            exit(1);
            break;
#ifdef TETRIS_DEBUG
        defualt:
            /* do nothing*/
            break;
#endif
        }
    }
}

static void cleanup_input_reader_module(void* arg)
{
    input_reader_t* const input_reader = (input_reader_t*)arg;
    cleanup_input_reader(input_reader);
}

extern void __pthread_register_cancel(__pthread_unwind_buf_t* __buf) __cleanup_fct_attribute;

#define my_pthread_cleanup_push(routine, arg)                                    \
    do {                                                                         \
        __pthread_unwind_buf_t __cancel_buf;                                     \
        void (*__cancel_routine)(void*) = (routine);                             \
        void* __cancel_arg = (arg);                                              \
        int __not_first_call = __sigsetjmp_cancel(__cancel_buf.__cancel_jmp_buf, \
            0);                                                                  \
        if (__glibc_unlikely(__not_first_call)) {                                \
            __cancel_routine(__cancel_arg);                                      \
            __pthread_unwind_next(&__cancel_buf);                                \
            /* NOTREACHED */                                                     \
        }                                                                        \
        __pthread_register_cancel(&__cancel_buf);                                \
    } while (0)

/* Remove a cleanup handler installed by the matching pthread_cleanup_push.
   If EXECUTE is non-zero, the handler function is called. */
#define my_pthread_cleanup_pop(execute)                                          \
    do {                                                                         \
        do {                                                                     \
            do {                                                                 \
            } while (0); /* Empty to allow label before pthread_cleanup_pop.  */ \
        } while (0);                                                             \
        __pthread_unregister_cancel(&__cancel_buf);                              \
        if (execute)                                                             \
            __cancel_routine(__cancel_arg);                                      \
    } while (0)

extern void __pthread_unregister_cancel(__pthread_unwind_buf_t* __buf) __cleanup_fct_attribute;

void* mainfunc_input_reader(void* arg)
{
    debug();

    tetris_play_manager_t* const play_manager = (tetris_play_manager_t*)arg;

    input_reader_t input_reader;
    init_input_reader(&input_reader);
    my_pthread_cleanup_push(cleanup_input_reader_module, NULL);

    while (true) {
        read_input(&input_reader);
        process_input_event(&input_reader.event_curr, play_manager);
        input_reader.event_prev = input_reader.event_curr;
    }
    return NULL;
}
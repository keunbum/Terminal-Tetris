#ifndef __INPUT_READER__H
#define __INPUT_READER__H

#include <linux/input.h>
#include <termios.h>
#include <pthread.h>

#include "error_handling.h"
#include "pthread_macro.h"

typedef int input_char_t;

typedef enum {
    READER_MODE_KEYBOARD,
    READER_MODE_GAMEPAD,
} reader_mode_t;

typedef pthread_spinlock_t input_reader_lock_t;

typedef struct {
    int fd;
    struct input_event event;
    reader_mode_t play_mode;
    struct termios old_termios;
    struct termios new_termios;

    input_reader_lock_t lock;
} input_reader_t;

static inline void init_input_reader_lock(input_reader_t* const out_input_reader)
{
    init_lock(out_input_reader->lock);
}

static inline void lock_input_reader(input_reader_t* const out_input_reader)
{
    debug();
    
    check_lock(out_input_reader->lock);
}

static inline void unlock_input_reader(input_reader_t* const out_input_reader)
{
    debug();

    check_unlock(out_input_reader->lock);
}

static inline void cleanup_input_reader_lock(input_reader_t* const out_input_reader)
{
    cleanup_lock(out_input_reader->lock);
}

void init_input_reader(input_reader_t* const);
void cleanup_input_reader(input_reader_t* const);
void read_input_event(input_reader_t* const);

#endif /* __INPUT_READER__H */
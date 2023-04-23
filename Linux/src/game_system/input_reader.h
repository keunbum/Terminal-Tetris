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

typedef struct {
    int fd;
    struct input_event event;
    reader_mode_t play_mode;
} input_reader_t;

void init_input_reader(input_reader_t* const);
void cleanup_input_reader(input_reader_t* const);
void read_input_event(input_reader_t* const);

#endif /* __INPUT_READER__H */
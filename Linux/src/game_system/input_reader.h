#ifndef __INPUT_READER__H
#define __INPUT_READER__H

#include <linux/input.h>
#include <termios.h>
#include <pthread.h>

#include "error_handling.h"
#include "pthread_macro.h"

#define EVENT_KEY_DEV "/dev/input/event2"
#define EVENT_NS_DEV "/dev/input/event6"

typedef int input_char_t;

// typedef enum {
//     DEVICE_MODE_KEYBOARD,
//     DEVICE_MODE_GAMEPAD,
// } device_mode_t;

typedef struct {
    int fd;
    // device_mode_t device_mode;
    struct input_event event;
    int device_event_num;
} input_reader_t;

void init_input_reader(input_reader_t* const out_reader, const char* device_path);
void cleanup_input_reader(input_reader_t* const);
void read_input_event(input_reader_t* const);

#endif /* __INPUT_READER__H */
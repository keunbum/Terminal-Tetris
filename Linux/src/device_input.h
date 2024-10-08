#ifndef __DEVICE_INPUT__H
#define __DEVICE_INPUT__H

#include <fcntl.h>
#include <linux/input.h>
#include <pthread.h>
#include <termios.h>

#include "error_handling.h"
#include "pthread_macro.h"

#define EV_KEYBOARD (120013)

// #define DEVICE_INPUT_KEYBOARD (2)
#define DEVICE_INPUT_CONTROLLER (6)

typedef struct {
    int fd;
    int device_event_num;
    struct input_event event;
} device_input_t;

void init_device_input(device_input_t* const out_in, int device_event_num, int flags);
void cleanup_device_input(device_input_t* const out_in);
bool read_device_input_event(device_input_t* const out_in);
int get_keyboard_event_num(void);

#endif /* __DEVICE_INPUT__H */
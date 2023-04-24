#ifndef __DEVICE_INPUT__H
#define __DEVICE_INPUT__H

#include <linux/input.h>
#include <termios.h>
#include <pthread.h>

#include "error_handling.h"
#include "pthread_macro.h"

#define DEVICE_INPUT_KEYBOARD (2)
#define DEVICE_INPUT_CONTROLLER_NS (6)
#define DEVICE_INPUT_CONTROLLER_XBOX (7)

typedef struct {
    int fd;
    int device_event_num;
    struct input_event event;
} device_input_t;

void init_device_input(device_input_t* const out_reader, int event_num);
void cleanup_device_input(device_input_t* const);
void read_device_input_event(device_input_t* const);

#endif /* __DEVICE_INPUT__H */
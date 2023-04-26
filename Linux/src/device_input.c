#include <stdio.h>
#include <unistd.h>

#include "chronometry.h"
#include "debug.h"
#include "device_input.h"

#define BUF_SIZE (64)

void init_device_input(device_input_t* const out_in, int event_num, int flags)
{
    debug();

    char buf[BUF_SIZE];
    out_in->device_event_num = event_num;
    sprintf(buf, "/dev/input/event%d", out_in->device_event_num);
    if ((out_in->fd = open(buf, flags)) == -1) {
        if (out_in->device_event_num == DEVICE_INPUT_KEYBOARD) {
            handle_error("open() error");
        }
        pthread_exit(NULL);
    }
}

void cleanup_device_input(device_input_t* const out_in)
{
    debug();

    if (close(out_in->fd) == -1) {
        handle_error("close() error");
    }
}

void read_device_input_event(device_input_t* const out_in)
{
    const ssize_t expected_read_size = (ssize_t)sizeof(struct input_event);
    if (read(out_in->fd, &out_in->event, expected_read_size) != expected_read_size) {
        handle_error("read() error");
    }
}

bool new_read_device_input_event(device_input_t* const out_in)
{
    const ssize_t expected_read_size = (ssize_t)sizeof(struct input_event);
    return read(out_in->fd, &out_in->event, expected_read_size) == expected_read_size;
}

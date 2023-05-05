#include <stdio.h>
#include <unistd.h>

#include "chronometry.h"
#include "debug.h"
#include "device_input.h"

#define BUF_SIZE (64)

void init_device_input(device_input_t* const out_in, int event_num, int flags)
{
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
    if (close(out_in->fd) == -1) {
        handle_error("close() error");
    }
}

/* return true; if something has been read.
   return false; if not */
bool read_device_input_event(device_input_t* const out_in)
{
    static const ssize_t s_expected_read_size = (ssize_t)sizeof(struct input_event);
    return read(out_in->fd, &out_in->event, s_expected_read_size) == s_expected_read_size;
}

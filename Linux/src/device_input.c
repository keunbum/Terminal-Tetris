#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "debug.h"
#include "device_input.h"

#define BUF_SIZE (64)

void init_device_input(device_input_t* const out_reader, int event_num)
{
    debug();

    static char s_buf[BUF_SIZE];

    out_reader->device_event_num = event_num;
    sprintf(s_buf, "/dev/input/event%d", out_reader->device_event_num);
    if ((out_reader->fd = open(s_buf, O_RDONLY)) == -1) {
        handle_error("open() error");
    }
}

void cleanup_device_input(device_input_t* const out_reader)
{
    debug();

    if (close(out_reader->fd) == -1) {
        handle_error("close() error");
    }
}

void read_device_input_event(device_input_t* const out_reader)
{
    const ssize_t expected_read_size = (ssize_t)sizeof(struct input_event);
    if (read(out_reader->fd, &out_reader->event, expected_read_size) != expected_read_size) {
        handle_error("read() error");
    }
}


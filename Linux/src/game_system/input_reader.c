#include <fcntl.h>
#include <unistd.h>

#include "debug.h"
#include "input_reader.h"

void init_input_reader(input_reader_t* const out_reader, const char* device_path)
{
    debug();

    // if ((out_reader->fd = open(EVENT_KEY_DEV, O_RDONLY)) == -1) {
    //     handle_error("open() error");
    // }
    if ((out_reader->fd = open(device_path, O_RDONLY)) == -1) {
        handle_error("open() error");
    }    
    // out_reader->device_mode = DEVICE_MODE_KEYBOARD;
}

void cleanup_input_reader(input_reader_t* const out_reader)
{
    debug();

    if (close(out_reader->fd) == -1) {
        handle_error("close() error");
    }
}

void read_input_event(input_reader_t* const out_reader)
{
    const ssize_t expected_read_size = (ssize_t)sizeof(struct input_event);
    if (read(out_reader->fd, &out_reader->event, expected_read_size) != expected_read_size) {
        handle_error("read() error");
    }
}

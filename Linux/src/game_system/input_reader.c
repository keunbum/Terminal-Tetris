#include <fcntl.h>
#include <unistd.h>

#include "debug.h"
#include "input_reader.h"

#define EVENT_KEY_DEV "/dev/input/event2"

void init_input_reader(input_reader_t* const out_reader)
{
    debug();

    if ((out_reader->fd = open(EVENT_KEY_DEV, O_RDONLY)) == -1) {
        handle_error("open() error");
    }
    // init_input_reader_lock(out_reader);
}

void cleanup_input_reader(input_reader_t* const out_reader)
{
    debug();

    // cleanup_input_reader_lock(out_reader);
    if (close(out_reader->fd) == -1) {
        handle_error("close() error");
    }
}

void read_input_event(input_reader_t* const out_reader)
{
    if (read(out_reader->fd, &out_reader->event, sizeof(struct input_event)) != sizeof(struct input_event)) {
        handle_error("in read_input_event() read() error");
    }
}

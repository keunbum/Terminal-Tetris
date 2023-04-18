#include <fcntl.h>
#include <unistd.h>

#include "debug.h"
#include "input_reader.h"

#define EVENT_KEY_DEV "/dev/input/event2"

static void turn_on_input_reader_raw(input_reader_t* const out_reader)
{
    debug();

    out_reader->new_termios = out_reader->old_termios;
    cfmakeraw(&out_reader->new_termios);
    tcsetattr(STDIN_FILENO, TCSANOW, &out_reader->new_termios);
}

static void turn_off_input_reader_raw(input_reader_t* const out_reader)
{
    debug();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &out_reader->old_termios);
}

void init_input_reader(input_reader_t* const out_reader)
{
    debug();

    if ((out_reader->fd = open(EVENT_KEY_DEV, O_RDONLY)) == -1) {
        handle_error("open() error");
    }
    tcgetattr(STDIN_FILENO, &out_reader->old_termios);
    turn_on_input_reader_raw(out_reader);
    // init_input_reader_lock(out_reader);
}

void cleanup_input_reader(input_reader_t* const out_reader)
{
    debug();

    // cleanup_input_reader_lock(out_reader);
    if (close(out_reader->fd) == -1) {
        handle_error("close() error");
    }
    turn_off_input_reader_raw(out_reader);
}

void read_input_event(input_reader_t* const out_reader)
{
    if (read(out_reader->fd, &out_reader->event, sizeof(struct input_event)) != sizeof(struct input_event)) {
        handle_error("in read_input_event() read() error");
    }
}

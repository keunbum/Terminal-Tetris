#include <stdbool.h>
#include <stdlib.h>

#include "debug.h"
#include "input_reader.h"

#define EVENT_KEY_DEV "/dev/input/event2"

static void turn_on_input_reader_raw(input_reader_t* const out_reader)
{
    out_reader->new_termios = out_reader->old_termios;
    cfmakeraw(&out_reader->new_termios);
    tcsetattr(STDIN_FILENO, TCSANOW, &out_reader->new_termios);
}

static void turn_off_input_reader_raw(input_reader_t* const out_reader)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &out_reader->old_termios);
}

static inline void read_key(input_reader_t* const out_reader)
{
    if (read(out_reader->fd, &out_reader->event_curr, sizeof(struct input_event)) != sizeof(struct input_event)) {
        handle_error("in read_key() read() error");
    }
}

void init_input_reader(input_reader_t* const out_reader)
{
    debug();

    if ((out_reader->fd = open(EVENT_KEY_DEV, O_RDONLY)) == -1) {
        handle_error("open() error");
    }
    tcgetattr(STDIN_FILENO, &out_reader->old_termios);
    turn_on_input_reader_raw(out_reader);
}

void cleanup_input_reader(input_reader_t* const out_reader)
{
    debug();

    close(out_reader->fd);
    turn_off_input_reader_raw(out_reader);
}

void read_input(input_reader_t* const out_reader)
{
    // 입력 이벤트 읽기
    struct input_event* const ev = &out_reader->event_curr;
    if (read(out_reader->fd, ev, sizeof(struct input_event)) != sizeof(struct input_event)) {
        handle_error("in read_input() read() error");
    }
}

#include <stdio.h>
#include <unistd.h>

#include "chronometry.h"
#include "debug.h"
#include "device_input.h"

#define BUF_SIZE (64)

void init_device_input(device_input_t* const out_in, int device_event_num, int flags)
{
    char buf[BUF_SIZE];
    out_in->device_event_num = device_event_num;
    sprintf(buf, "/dev/input/event%d", out_in->device_event_num);
    if ((out_in->fd = open(buf, flags)) == -1) {
        sprintf(buf, "open() error, event: %d", device_event_num);
        handle_error(buf);

        /* that.. let's leave it for now because it might use multi-threading. */
        // if (out_in->device_event_num == DEVICE_INPUT_KEYBOARD) {
        //     handle_error("open() error");
        // }
        // pthread_exit(NULL);
    }
}

void cleanup_device_input(device_input_t* const out_in)
{
    if (close(out_in->fd) == -1) {
        handle_error("close() error");
    }
}

/* return whether the input was read correctly. */
bool read_device_input_event(device_input_t* const out_in)
{
    static const ssize_t s_expected_read_size = (ssize_t)sizeof(struct input_event);
    const ssize_t actual_read_size = read(out_in->fd, &out_in->event, s_expected_read_size);
    return actual_read_size == s_expected_read_size;
}

int get_keyboard_event_num(void)
{
    FILE* pipe = popen("grep -E 'Handlers|EV=' /proc/bus/input/devices | grep -B1 'EV=120013' | grep -Eo 'event[0-9]+'", "r");
    if (pipe == NULL) {
        handle_error("popen() error");
    }
    int ret = 0;
    if (fscanf(pipe, "event%d\n", &ret) != 1) {
        handle_error("fscanf() error");
    }
    pclose(pipe);
    return ret;
}
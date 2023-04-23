#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int test_evdev_arr(void)
{
    int gamepad = open("/dev/input/by-id/usb-045e_0291-event-joystick",
        O_RDONLY | O_NONBLOCK);
    assert(gamepad != -1);
    int gamepad_debug_event_count = 0;
    int gamepad_button_A_down = 0;
    int gamepad_button_B_down = 0;
    int gamepad_stick_left_x = 0;
    int gamepad_stick_left_y = 0;
    for (;;) {
        struct input_event events[8]; // 8 events per frame is pretty extreme, more like 1 or 2, sometimes as high as 4
        int r1 = read(gamepad, events, sizeof events);
        if (r1 != -1) {
            int new_event_count = r1 / sizeof(struct input_event);
            for (int evi = 0; evi < new_event_count; evi++) {
                struct input_event ev = events[evi];
                switch (ev.type) {
                case EV_ABS: {
                    switch (ev.code) {
                    case ABS_X:
                        gamepad_stick_left_x = ev.value;
                        break;
                    case ABS_Y:
                        gamepad_stick_left_y = ev.value;
                        break;
                    }
                } break;
                case EV_KEY: {
                    switch (ev.code) {
                    case BTN_A:
                        gamepad_button_A_down = ev.value;
                        break;
                    case BTN_B:
                        gamepad_button_B_down = ev.value;
                        break;
                    }
                } break;
                }
                gamepad_debug_event_count++;
            }
        }

        assert(r1 != -1 || errno == EWOULDBLOCK || errno == EAGAIN);

        printf("Pos %d Left stick:%d,%d  A:%d B:%d \r",
            gamepad_debug_event_count,
            gamepad_stick_left_x,
            gamepad_stick_left_y,
            gamepad_button_A_down,
            gamepad_button_B_down);
    }
    usleep(20 * 1000);
    return 0;
}
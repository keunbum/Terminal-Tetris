#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#define EVENT_DEV "/dev/input/event2"

int test_evdev(void)
{
    int event_fd;
    struct input_event ev;

    // 이벤트 장치 파일 열기
    if ((event_fd = open(EVENT_DEV, O_RDONLY)) == -1) {
        perror("Could not open event device");
        return 1;
    }

    printf("Press the 'Esc' key to exit\n");
    while (1) {
        // 입력 이벤트 읽기
        if (read(event_fd, &ev, sizeof(struct input_event)) != sizeof(struct input_event)) {
            perror("Could not read event");
            return 1;
        }

        assert(ev.type != EV_ABS);

        // 키 입력 처리
        if (ev.type == EV_KEY && (ev.value == 1 || ev.value == 2)) {
            if (ev.code == KEY_UP) {
                printf("Up arrow key pressed\n");
            } else if (ev.code == KEY_DOWN) {
                printf("Down arrow key pressed\n");
            } else if (ev.code == KEY_LEFT) {
                printf("Left arrow key pressed\n");
            } else if (ev.code == KEY_RIGHT) {
                printf("Right arrow key pressed\n");
            } else if (ev.code == KEY_SPACE) {
                printf("Space bar pressed\n");
            } else if (ev.code == KEY_Z) {
                printf("'Z' key pressed\n");
            } else if (ev.code == KEY_X) {
                printf("'X' key pressed\n");
            } else if (ev.code == KEY_C) {
                printf("'C' key pressed\n");
            } else if (ev.code == KEY_ESC) {
                break;
            }
        }

        // 'A' 버튼 입력 처리
        if (ev.type == EV_KEY && ev.code == BTN_A && ev.value == 1) {
            printf("'A' button pressed\n");
            break;
        }
    }

    // 이벤트 장치 파일 닫기
    close(event_fd);

    return 0;
}

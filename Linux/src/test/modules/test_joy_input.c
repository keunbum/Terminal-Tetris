#include <fcntl.h>
#include <linux/joystick.h>
#include <stdio.h>
#include <unistd.h>

#define JOY_DEV "/dev/input/js0"

#define JOY_VALUE

int test_joy_input(void)
{
    int joy_fd;
    struct js_event js;

    // 게임 패드 장치 파일 열기
    if ((joy_fd = open(JOY_DEV, O_RDONLY)) == -1) {
        perror("Could not open joystick device");
        return 1;
    }

    // 논블로킹 모드 설정
    fcntl(joy_fd, F_SETFL, O_NONBLOCK);

    printf("Press the 'A' button to exit\n");
    while (1) {
        // 입력 이벤트 읽기
        if (read(joy_fd, &js, sizeof(struct js_event)) != sizeof(struct js_event)) {
            perror("Could not read joystick event");
            return 1;
        }

        // 버튼 입력 처리
        if (js.type == JS_EVENT_BUTTON) {
            if (js.number == 0 && js.value == 1) {
                printf("A button pressed\n");
                break;
            }
            // LB, LT, RB, RT 버튼 입력 처리
            if (js.number == 4 && js.value == 1) {
                printf("LB button pressed\n");
            } else if (js.number == 6 && js.value == 1) {
                printf("LT button pressed\n");
            } else if (js.number == 5 && js.value == 1) {
                printf("RB button pressed\n");
            } else if (js.number == 7 && js.value == 1) {
                printf("RT button pressed\n");
            } else if (js.number == 9 && js.value == 1) {
                printf("Menu button pressed\n");
                break;
            }
            continue;
        }
        // 조이스틱 입력 처리
        if (js.type == JS_EVENT_AXIS) {
            if (js.number == 0) {
                printf("Left joystick X axis: %d\n", js.value);
            } else if (js.number == 1) {
                printf("Left joystick Y axis: %d\n", js.value);
                break;
            }
            continue;
        }
    }

    // 게임 패드 장치 파일 닫기
    close(joy_fd);

    return 0;
}
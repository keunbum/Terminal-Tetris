#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>

int test_evdev_nonblock(int argc, char *argv[]) {
    int fd;
    struct input_event ev;
    char buf[128];
    if (argc < 2) {
        strcpy(buf, "/dev/input/event2");
        // printf("Usage: %s /dev/input/eventX\n", argv[0]);
        // return 1;
    }
    argv[1] = buf;
    fd = open(argv[1], O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("Cannot open device");
        return 1;
    }

    for (int i = 0; i < 1e9; ++i) {
        ssize_t n = read(fd, &ev, sizeof(ev));
        if (n == -1) {
            // No data available
            usleep(10000); // sleep for 10ms
            continue;
        }
        if (n != sizeof(ev)) {
            perror("Error reading event");
            close(fd);
            return 1;
        }
        printf("Event: time %ld.%06ld, type %d, code %d, value %d\n",
               ev.time.tv_sec, ev.time.tv_usec, ev.type, ev.code, ev.value);
    }

    close(fd);
    return 0;
}
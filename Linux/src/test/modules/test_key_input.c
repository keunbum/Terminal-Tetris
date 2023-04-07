#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

int test_key_input(int argc, char *argv[])
{
    int fd;
    struct input_event ev;

    if (argc < 2) {
        printf("Usage: %s /dev/input/eventX\\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Cannot open device");
        return 1;
    }

    while (1) {
        read(fd, &ev, sizeof(ev));
        printf("Type: %d, Code: %d, Value: %d\\n", ev.type, ev.code, ev.value);
    }

    close(fd);
    return 0;
}
#include <stdio.h>
int test_system() {
    char buffer[128];
    FILE *pipe = popen("grep -E 'Handlers|EV=' /proc/bus/input/devices | grep -B1 'EV=120013' | grep -Eo 'event [0-9]+'", "r");
    if (!pipe) return 1;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);
    }
    pclose(pipe);
    return 0;
}
#include <wchar.h>
#include <wctype.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>

#include "localize/localize.h"
#include "test.h"

extern int test_termios(int, char*[]);
extern int test_evdev(void);
extern int test_joy_input(void);
extern int test_chronometry(void);
extern int test_evdev_arr(void);
extern int test_evdev_nonblock(int, char*[]);
extern int test_system(void);

int test_module(int argc, char* argv[])
{
    localize();
    (void)argc;
    (void)argv;

    wprintf(L"\e[0;%dm", 35);
    wprintf(L"\e[%dm", 43);
    wprintf(L"HI!\n");
    wprintf(L"Hello!!\n");
    return 0;
    // return test_system();
}
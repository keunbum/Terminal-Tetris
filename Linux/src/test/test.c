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
extern int test_gettimeofday(void);

int test_module(int argc, char* argv[])
{
    localize();
    (void)argc;
    (void)argv;

    return test_gettimeofday();
}
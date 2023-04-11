#include <wchar.h>
#include <wctype.h>

#include "localize/localize.h"
#include "test.h"

extern int test_termios(int, char*[]);
extern int test_evdev(void);
extern int test_joy_input(void);

int test_module(int argc, char* argv[])
{
    localize();
    (void)argc;
    (void)argv;
    return test_evdev();
}
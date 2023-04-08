#include <wchar.h>
#include <wctype.h>

#include "localize/localize.h"
#include "test.h"

extern int test_termios(int, char*[]);

int test_module(int argc, char* argv[])
{
    localize();

    return test_termios(argc, argv);
}
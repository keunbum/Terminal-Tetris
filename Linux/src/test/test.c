#include <wchar.h>
#include <wctype.h>

#include "test.h"
#include "localize/localize.h"

extern int test_timer(int, char*[]);
extern int test_wmove_cursor(int, char*[]);

int test_module(int argc, char* argv[])
{
    localize();
    return 0;
    //    return test_wmove_cursor(argc, argv);
    //    return test_timer(argc, argv);
}
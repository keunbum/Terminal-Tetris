#include <wchar.h>
#include <wctype.h>

#include "test.h"
#include "localize/localize.h"

extern int test_timer(int, char*[]);
extern int test_wmove_cursor(int, char*[]);

int test_module()
{
    localize();

    for (int i = 0; i < 8; ++i) {
        wprintf(L"\e[0;3%dm", i);
        wprintf(L"%lc%lc%lc%lc%lc%lc%lc%lcABCDEFG\n", (0x2588), (0x2588), (0x2591), (0x2591), (0x2B1B), (0x2B1C), (0x25A0), (0x25A1));
    }
    wprintf(L"\e[0m");
    // wprintf(L"\e[1;31m"); // red
    // wprintf(L"\U0001f5ff Hi!\n");
    // wprintf(L"\e[1;30m"); // black
    // wprintf(L"\U0001f5ff Hi!\n");
    // wprintf(L"\e[1;37m"); // black
    // wprintf(L"\U0001f5ff Hi!\n");
    // wprintf(L"\n");
    // wprintf(L"\e[0m");

    // wprintf(L"\e[4;31m"); // red
    // wprintf(L"\U0001f5ff Hi!\n");
    // wprintf(L"\e[4;30m"); // black
    // wprintf(L"\U0001f5ff Hi!\n");
    // wprintf(L"\e[4;37m"); // black
    // wprintf(L"\U0001f5ff Hi!\n");
    // wprintf(L"\n");
    // wprintf(L"\e[0m");
    
    // wprintf(L"\e[4;41m"); // red
    // wprintf(L"\U0001f5ff Hi!\n");
    // wprintf(L"\e[4;40m"); // black
    // wprintf(L"\U0001f5ff Hi!\n");
    // wprintf(L"\e[4;47m"); // black
    // wprintf(L"\U0001f5ff Hi!\n");
    // wprintf(L"\n");
    // wprintf(L"\e[0m");
    
    // wprintf(L"\e[0;101m"); // red
    // wprintf(L"\U0001f5ff Hi!\n");
    // wprintf(L"\e[0;100m"); // black
    // wprintf(L"\U0001f5ff Hi!\n");
    // wprintf(L"\e[0;107m"); // black
    // wprintf(L"\U0001f5ff Hi!\n");
    // wprintf(L"\n");
    // wprintf(L"\e[0m");
    
    return 0;
    //    return test_wmove_cursor(argc, argv);
    //    return test_timer(argc, argv);
}
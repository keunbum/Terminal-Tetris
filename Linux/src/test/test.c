#include <wchar.h>
#include <wctype.h>

#include "test.h"
#include "localize/localize.h"

extern int test_timer(int, char*[]);
extern int test_wmove_cursor(int, char*[]);

int test_module()
{
    localize();

    // for (int i = 0; i < 8; ++i) {
    //     wprintf(L"\e[0;3%dm", i);
    //     wprintf(L"%lc%lc%lc%lc%lc%lc%lc%lcABCDEFG\n", (0x2588), (0x2588), (0x2591), (0x2591), (0x2B1B), (0x2B1C), (0x25A0), (0x25A1));
    // }
    // wprintf(L"\e[0m");

// #include "tetris/tetromino/block.h"

//Regular background
// #define BLKB "\e[40m"
// #define REDB "\e[41m"
// #define GRNB "\e[42m"
// #define YELB "\e[43m"
// #define BLUB "\e[44m"
// #define MAGB "\e[45m"
// #define CYNB "\e[46m"
// #define WHTB "\e[47m"

// #define reset "\e[0m"
// #define CRESET "\e[0m"
// #define COLOR_RESET "\e[0m"


//     wchar_t block_code = BLOCK_WPRINT_LIGHT_LARGE_SQUARE;

//     wprintf(L"%lc", block_code);
//     wprintf(L"\e[41m");
//     wprintf(L"%lc%lc%lc", block_code, block_code, block_code);
//     wprintf(L"\e[0m");
//     wprintf(L"%lc\n", block_code);

//     wprintf(L"%lc", block_code);
//     wprintf(L"%lc%lc%lc\n", block_code, block_code, block_code);
//     wprintf(L"%lc", block_code);
//     wprintf(L"%lc%lc%lc\n", block_code, block_code, block_code);
//     wprintf(L"%lc", block_code);
//     wprintf(L"%lc%lc%lc\n", block_code, block_code, block_code);

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
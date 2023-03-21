#include "draw_tool/cursor.h"

#define EMPTY_LENGTH (20)

int test_wmove_cursor(int argc, char*[])
{
    wclear();
    wchar_t buf[EMPTY_LENGTH + 1];
    wmemset(buf, ' ', EMPTY_LENGTH);
    wprintf(L"%s", buf);
    wprintf(L"                  ");
    wprintf(L"Enter your number in the box below\n");
    wmove_cursor_right_by(3);
    wprintf(L"+-----------------+");
//    wprintf(L"|                 |");
//    wprintf(L"+-----------------+");
    return 0;
}
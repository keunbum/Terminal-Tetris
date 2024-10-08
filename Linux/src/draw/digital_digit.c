#include "digital_digit.h"
#include "cursor.h"
#include "debug.h"
#include "draw_tool.h"

const digital_digit5_t G_DIGITAL_DIGIT5S[] = {
    {
        L"+---+",
        L"|   |",
        L"+   +",
        L"|   |",
        L"+---+",
    },
    {
        L"    +",
        L"    |",
        L"    +",
        L"    |",
        L"    +",
    },
    {
        L"+---+",
        L"    |",
        L"+---+",
        L"|    ",
        L"+---+",
    },
    {
        L"+---+",
        L"    |",
        L"+---+",
        L"    |",
        L"+---+",
    },
    {
        L"+   +",
        L"|   |",
        L"+---+",
        L"    |",
        L"    +",
    },
    {
        L"+---+",
        L"|    ",
        L"+---+",
        L"    |",
        L"+---+",
    },
    {
        L"+---+",
        L"|    ",
        L"+---+",
        L"|   |",
        L"+---+",
    },
    {
        L"+---+",
        L"    |",
        L"    +",
        L"    |",
        L"    +",
    },
    {
        L"+---+",
        L"|   |",
        L"+---+",
        L"|   |",
        L"+---+",
    },
    {
        L"+---+",
        L"|   |",
        L"+---+",
        L"    |",
        L"    +",
    },
};

const digital_digit5_t G_DIGITAL_DIGIT5_EMPTY = {
    L"     ",
    L"     ",
    L"     ",
    L"     ",
    L"     ",
};

void wdraw_digital_digit5_at(const digital_digit5_t digit, int pos_x, int pos_y)
{
    wdraw_rows_newline_at_r(DIGITAL_DIGIT5_HEIGHT, (const wchar_t**)digit, DIGITAL_DIGIT5_WIDTH, pos_x, pos_y);
    fflush(stdout);
}
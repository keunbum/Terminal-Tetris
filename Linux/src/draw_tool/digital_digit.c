#include "digital_digit.h"
#include "debug/debug.h"
#include "draw_tool/cursor.h"
#include "draw_tool/draw_tool.h"

const digital_digit_t G_DIGITAL_DIGITS[] = {
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

const digital_digit_t G_DIGITAL_DIGIT_EMPTY = {
    L"     ",
    L"     ",
    L"     ",
    L"     ",
    L"     ",
};

void wdraw_digital_digit_at_r(const digital_digit_t digit, int pos_x, int pos_y)
{

    debug();

    wdraw_rows_newline_at_r(DIGITAL_DIGIT_HEIGHT, digit, DIGITAL_DIGIT_WIDTH, pos_x, pos_y);
}
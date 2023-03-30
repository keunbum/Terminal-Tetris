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

void wdraw_digital_digit_at_r(const digital_digit_t digit, int x, int y)
{

    debug();

    wdraw_rows_newline_at_r(DIGITAL_DIGIT_HEIGHT, digit, DIGITAL_DIGIT_WIDTH, x, y);

    pthread_mutex_lock(&g_cursor_mutex);
    wgotoxy(x, y);
    for (int i = 0; i < DIGITAL_DIGIT_HEIGHT; ++i) {
        wdraw_row_newline(digit[i], DIGITAL_DIGIT_WIDTH);
    }
    wdraw_newline();
    pthread_mutex_unlock(&g_cursor_mutex);
}
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include "cursor.h"
#include "debug.h"
#include "draw_tool.h"

static void wdraw_unit_matrix_at(wchar_t ch, int x, int y)
{
    debug();

    wgotoxy(x, y);
    wdraw_unit_matrix(ch);
}

// [sx, ex)
static void wdraw_col_matrix_at(wchar_t ch, int sx, int ex, int sy)
{
    debug();

    wgotoxy(sx, sy);
    for (int i = sx; i < ex; i += 1) {
        wdraw_unit_matrix_at(ch, i, sy);
    }
}

void wdraw_unit_matrix(wchar_t wch)
{
    debug();

    putwc(wch, stdout);
}

// [sy, ey)
void wdraw_row_matrix_at(wchar_t ch, int sx, int sy, int ey)
{
    debug();

    wgotoxy(sx, sy);
    for (int j = sy; j < ey; j += 1) {
        wdraw_unit_matrix(ch);
    }
}

void wdraw_boundary_at_with(wchar_t hor_block, wchar_t ver_block, int height, int width, int sx, int sy, wchar_t top_lft, wchar_t top_rgt, wchar_t bot_lft, wchar_t bot_rgt)
{
    debug();

    int x0 = sx;
    int x1 = x0 + height - 1;
    int y0 = sy;
    int y1 = y0 + width - 1;

    wdraw_unit_matrix_at(top_lft, x0, y0);
    wdraw_unit_matrix_at(top_rgt, x0, y1);
    wdraw_unit_matrix_at(bot_lft, x1, y0);
    wdraw_unit_matrix_at(bot_rgt, x1, y1);

    wdraw_row_matrix_at(hor_block, x0, y0 + 1, y1);
    wdraw_row_matrix_at(hor_block, x1, y0 + 1, y1);

    wdraw_col_matrix_at(ver_block, x0 + 1, x1, y0);
    wdraw_col_matrix_at(ver_block, x0 + 1, x1, y1);
}

// height and width both means total length
void wdraw_boundary_at(wchar_t hor_block, wchar_t ver_block, int height, int width, int sx, int sy)
{
    debug();

    wdraw_boundary_at_with(hor_block, ver_block, height, width, sx, sy, UNIT_MATRIX_CORNER_TOP_LEFT, UNIT_MATRIX_CORNER_TOP_RIGHT, UNIT_MATRIX_CORNER_BOT_LEFT, UNIT_MATRIX_CORNER_BOT_RIGHT);
}

void wset_row_line(wchar_t* const buf, int length, wchar_t beg, wchar_t mid, wchar_t end)
{
    debug();

    buf[0] = beg;
    for (int i = 1; i < length - 1; ++i) {
        buf[i] = mid;
    }
    //    wmemset(buf + 1, mid, length - 2);
    buf[length - 1] = end;
    buf[length] = L'\0';
}

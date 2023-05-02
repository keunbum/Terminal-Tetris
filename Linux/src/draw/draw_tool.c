#include <assert.h>
#include <unistd.h>

#include "cursor.h"
#include "debug.h"
#include "draw_tool.h"

#define MAX_BUF_SIZE (256)

// [sx, ex)
static void wdraw_col_matrix_at(wchar_t wch, int sx, int ex, int sy)
{
    wgotoxy(sx, sy);
    for (int _ = 0; _ < ex - sx; ++_) {
        wdraw_unit_matrix(wch);
        fputws(L"\e[1B\e[1D", stdout);
    }
}

// [sy, ey)
static void wdraw_row_matrix_at(wchar_t wch, int sx, int sy, int ey)
{
    static wchar_t s_wbuf[MAX_BUF_SIZE];
    int n = ey - sy;
    for (int i = 0; i < n; ++i) {
        s_wbuf[i] = wch;
    }
    s_wbuf[n] = L'\0';
    wdraw_row_at(s_wbuf, sx, sy);
}

/* height and width both means total length */
void wdraw_boundary_at_with(wchar_t hor_block, wchar_t ver_block, int height, int width, int start_pos_x, int start_pos_y, wchar_t top_lft, wchar_t top_rgt, wchar_t bot_lft, wchar_t bot_rgt)
{
    int x0 = start_pos_x;
    int x1 = x0 + height - 1;
    int y0 = start_pos_y;
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

void wset_row_line(wchar_t* const wbuf, int length, wchar_t beg, wchar_t mid, wchar_t end)
{
    wbuf[0] = beg;
    for (int i = 1; i < length - 1; ++i) {
        wbuf[i] = mid;
    }
    wbuf[length - 1] = end;
    wbuf[length] = L'\0';
}

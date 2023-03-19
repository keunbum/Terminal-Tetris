#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include "debug/debug.h"
#include "game/draw_tool/cursor.h"
#include "game/draw_tool/draw_tool.h"
#include "util/util.h"

static void draw_unit_matrix(wchar_t ch)
{
    putwc(ch, stdout);
}

static void draw_unit_matrix_at(wchar_t ch, int x, int y)
{
    wgotoxy(x, y);
    draw_unit_matrix(ch);
}

// [sx, ex)
static void draw_col_matrix_at(wchar_t ch, int sx, int ex, int sy)
{
    wgotoxy(sx, sy);
    for (int i = sx; i < ex; i += 1) {
        draw_unit_matrix_at(ch, i, sy);
    }
}

// [sy, ey)
void draw_row_matrix_at(wchar_t ch, int sx, int sy, int ey)
{
    wgotoxy(sx, sy);
    for (int j = sy; j < ey; j += 1) {
        draw_unit_matrix(ch);
    }
}

void draw_boundary_at_with(wchar_t hor_block, wchar_t ver_block, int height, int width, int sx, int sy, wchar_t top_lft, wchar_t top_rgt, wchar_t bot_lft, wchar_t bot_rgt)
{
    int x0 = sx;
    int x1 = x0 + height - 1;
    int y0 = sy;
    int y1 = y0 + width - 1;

    draw_unit_matrix_at(top_lft, x0, y0);
    draw_unit_matrix_at(top_rgt, x0, y1);
    draw_unit_matrix_at(bot_lft, x1, y0);
    draw_unit_matrix_at(bot_rgt, x1, y1);
    
    draw_row_matrix_at(hor_block, x0, y0 + 1, y1);
    draw_row_matrix_at(hor_block, x1, y0 + 1, y1);

    draw_col_matrix_at(ver_block, x0 + 1, x1, y0);
    draw_col_matrix_at(ver_block, x0 + 1, x1, y1);
}

// height and width both means total length
void draw_boundary_at(wchar_t hor_block, wchar_t ver_block, int height, int width, int sx, int sy)
{
    draw_boundary_at_with(hor_block, ver_block,height, width, sx, sy, UNIT_MATRIX_CORNER_TOP_LEFT, UNIT_MATRIX_CORNER_TOP_RIGHT, UNIT_MATRIX_CORNER_BOT_LEFT, UNIT_MATRIX_CORNER_BOT_RIGHT);
}

void draw_row_blocks(const block_t* row)
{
    my_assert(row != NULL);

    static const wchar_t S_BLOCK_UNICODE_FOR_DRAW[] = { BLOCK_FULL, BLOCK_EMPTY };
    for (int j = 0; row[j]; ++j) {
        draw_unit_matrix(S_BLOCK_UNICODE_FOR_DRAW[encode_block(row[j])]);
    }
}
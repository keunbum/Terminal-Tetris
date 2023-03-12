#include <assert.h>
#include <stdio.h>

#include "util/util.h"
#include "draw_manager/draw_manager.h"
#include "debug/local_debug.h"
#include "game_play/game_play_screen.h"
#include "game_play/game_play_grid_matrix.h"

static void draw_unit_matrix(wchar_t ch)
{
    putwc(ch, stdout);
}

static void draw_unit_matrix_at(wchar_t ch, int x, int y)
{
    wgotoxy(x, y);
    draw_unit_matrix(ch);
}

// [sy, ey)
static void draw_row_matrix_at(wchar_t ch, int sx, int sy, int ey)
{
    wgotoxy(sx, sy);
    for (int j = sy; j < ey; j += 1)
    {
        draw_unit_matrix(ch);
    }
}

// [sx, ex)
static void draw_col_matrix_at(wchar_t ch, int sx, int ex, int sy)
{
    wgotoxy(sx, sy);
    for (int i = sx; i < ex; i += 1)
    {
        draw_unit_matrix_at(ch, i, sy);
    }
}

static void draw_boundary_at_with(wchar_t hor_block, wchar_t ver_block, int height, int width, int sx, int sy, wchar_t top_lft, wchar_t top_rgt, wchar_t bot_lft, wchar_t bot_rgt)
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

// height, width both means total length
static void draw_boundary_at(wchar_t hor_block, wchar_t ver_block, int height, int width, int sx, int sy)
{
    draw_boundary_at_with(hor_block, ver_block,height, width, sx, sy, UNIT_MATRIX_CORNER_TOP_LEFT, UNIT_MATRIX_CORNER_TOP_RIGHT, UNIT_MATRIX_CORNER_BOT_LEFT, UNIT_MATRIX_CORNER_BOT_RIGHT);
}

static void draw_outside_area_at(int sx, int sy)
{
    draw_boundary_at_with(UNIT_MATRIX_HOR_LINE_THIN, UNIT_MATRIX_VER_LINE_THIN, GAME_PLAY_SCREEN_HEIGHT, GAME_PLAY_SCREEN_WIDTH, sx, sy,
        UNIT_MATRIX_CORNER_TOP_LEFT_THIN,
        UNIT_MATRIX_CORNER_TOP_RIGHT_THIN,
        UNIT_MATRIX_CORNER_BOT_LEFT_THIN,
        UNIT_MATRIX_CORNER_BOT_RIGHT_THIN
    );
}

static void draw_inside_area_at(int sx, int sy)
{
    draw_boundary_at(UNIT_MATRIX_HOR_LINE, UNIT_MATRIX_VER_LINE, GAME_PLAY_GRID_MATRIX_HEIGHT, GAME_PLAY_GRID_MATRIX_WIDTH, sx, sy);
    int small_h = GAME_PLAY_GRID_MATRIX_HEIGHT - 2;
    int small_w = GAME_PLAY_GRID_MATRIX_WIDTH - 2;
    wgotoxy(sx + 1, sy + 1);
    forn(i, small_h)
    {
        draw_row_matrix_at(BLOCK_EMPTY, sx + 1 + i, sy + 1, sy + 1 + small_w / 2);
    }
}

void draw_whole_screen_at(int sx, int sy)
{
    wclear();
    wenable_cursor();
    //wdisable_cursor();
    draw_outside_area_at(sx, sy);
    draw_inside_area_at(sx + GAME_PLAY_GRID_MATRIX_START_POS_X, sy + GAME_PLAY_GRID_MATRIX_START_POS_Y);
}

void draw_a_tetromino_at(const tetromino_t *t, int sx, int sy)
{
    const tetromino_symbol_t* symbol = s_tetromino_symbols + t->tetromino_id;
    int x_offset = 0;
    int y_offset = -1;

    wgotoxy(sx + x_offset, sy + y_offset);
    for (int i = 0; symbol->blocks2d[i]; ++i)
    {
        const block_t *s = symbol->blocks2d[i];
        Assert(s != NULL);
        for (int j = 0; s[j]; ++j)
        {
            static const wchar_t blocks[] = { BLOCK_FULL, BLOCK_EMPTY };
            draw_unit_matrix(blocks[(int) (s[j] - '1')]);
        }
        draw_newline();
    }
}

void draw_a_default_tetromino_at(int id, int sx, int sy)
{
    tetromino_t t = {
        .tetromino_id = id,
        .dir = DIR_BOT,
        .color = COLOR_WHITE,
    };
    draw_a_tetromino_at(&t, sx, sy);
}

static void decode_seconds(int sec, int* const out_hh, int* const out_mm, int* const out_ss)
{
    *out_hh = sec / 3600;
    *out_mm = (sec % 3600) / 60;
    *out_ss = sec % 60;
}

static void draw_sec_to_hhmmss(int sec)
{
    int hh, mm, ss;
    decode_seconds(sec, &hh, &mm, &ss);
    wprintf(L"Time: %02d:%02d:%02d\n", hh, mm, ss);
}

void draw_game_play_timer_at(int sx, int sy, int sec)
{
    wgotoxy(sx, sy);
    draw_sec_to_hhmmss(sec);
}
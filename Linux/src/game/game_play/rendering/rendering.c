

#include "rendering.h"
#include "debug/debug.h"
#include "draw_tool/cursor.h"
#include "draw_tool/draw_tool.h"
#include "game/game_play/tetromino/tetromino.h"

static void draw_row_blocks(const block_t* row)
{
    my_assert(row != NULL);

    static const wchar_t S_BLOCK_UNICODE_FOR_DRAW[] = { BLOCK_FULL, BLOCK_EMPTY };
    for (int j = 0; row[j]; ++j) {
        draw_unit_matrix(S_BLOCK_UNICODE_FOR_DRAW[encode_block(row[j])]);
    }
}

void draw_a_tetromino(const tetromino_t* t)
{
    static const int X_OFFSET = 0;
    static const int Y_OFFSET = -1;
    const tetromino_symbol_t* symbol = g_tetromino_symbols + t->tetromino_id;

    wgotoxy(t->pos_x + X_OFFSET, t->pos_y + Y_OFFSET);
    for (int i = 0; i < symbol->height; ++i) {
        draw_row_blocks(symbol->grid[i]);
        draw_newline();
    }
}


#include "rendering.h"
#include "debug/debug.h"
#include "draw_tool/cursor.h"
#include "draw_tool/draw_tool.h"
#include "game/game_play/tetromino/tetromino.h"

static void draw_row_blocks(const block_t* row)
{
    debug();

    my_assert(row != NULL);

    static const wchar_t S_BLOCK_UNICODE_FOR_DRAW[] = { BLOCK_BLACK_LARGE_SQUARE, BLOCK_WHITE_LARGE_SQUARE };
    for (int j = 0; row[j]; ++j) {
        wdraw_unit_matrix(S_BLOCK_UNICODE_FOR_DRAW[encode_block(row[j])]);
    }
}

void draw_a_tetromino(const tetromino_t* t)
{
    debug();
    
    my_assert(t != NULL);

    static const int X_OFFSET = 0;
    static const int Y_OFFSET = -1;
    const tetromino_symbol_t* symbol = G_TETROMINO_SYMBOLS + t->symbol_id;

    wgotoxy(t->pos_x + X_OFFSET, t->pos_y + Y_OFFSET);
    for (int i = 0; i < symbol->height; ++i) {
        draw_row_blocks(symbol->grid[i]);
        wdraw_newline();
    }
}
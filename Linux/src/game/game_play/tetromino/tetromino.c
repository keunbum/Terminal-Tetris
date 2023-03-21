#include "debug/debug.h"
#include "draw_tool/cursor.h"
#include "draw_tool/draw_tool.h"
#include "game/game_play/tetromino/tetromino.h"

const tetromino_symbol_t g_tetromino_symbols[TOTAL_TETROMINO_NUM] = {
    // I
    {
        1,
        {
            "1111",
        },
    },
    // O
    {
        2,
        {
            "11",
            "11",
        },
    },
    // T
    {
        2,
        {
            "111",
            "010",
        },
    },
    // J
    {
        3,
        {
            "01",
            "01",
            "11",
        },
    },
    // L
    {
        3,
        {
            "10",
            "10",
            "11",
        },
    },
    // S
    {
        2,
        {
            "011",
            "110",
        },
    },
    // Z
    {
        2,
        {
            "110",
            "011",
        },
    },
};

/*
static void draw_row_blocks(const block_t* row)
{
    my_assert(row != NULL);

    static const wchar_t S_BLOCK_UNICODE_FOR_DRAW[] = { BLOCK_FULL, BLOCK_EMPTY };
    for (int j = 0; row[j]; ++j) {
        draw_unit_matrix(S_BLOCK_UNICODE_FOR_DRAW[encode_block(row[j])]);
    }
}*/

int encode_block(char ch)
{
    return (int)(ch - '1');
}

/*
void draw_a_tetromino_at(const tetromino_t* t, int sx, int sy)
{
    static const int X_OFFSET = 0;
    static const int Y_OFFSET = -1;
    const tetromino_symbol_t* symbol = g_tetromino_symbols + t->tetromino_id;

    wgotoxy(sx + X_OFFSET, sy + Y_OFFSET);
    for (int i = 0; i < symbol->height; ++i) {
        draw_row_blocks(symbol->grid[i]);
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
*/
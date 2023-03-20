#include "game/game_play/common/tetromino/tetromino.h"
#include "game/draw_tool/cursor.h"
#include "game/draw_tool/draw_tool.h"
#include "util/util.h"

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

int encode_block(char ch)
{
    return (int)(ch - '1');
}

void draw_a_tetromino_at(const tetromino_t* t, int sx, int sy)
{
    static const int X_OFFSET = 0;
    static const int Y_OFFSET = -1;
    const tetromino_symbol_t* symbol = g_tetromino_symbols + t->tetromino_id;

    wgotoxy(sx + X_OFFSET, sy + Y_OFFSET);
    forn(i, symbol->height) {
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
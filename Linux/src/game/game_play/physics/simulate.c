#include <stdbool.h>

#include "debug/debug.h"
#include "draw_tool/cursor.h"
#include "draw_tool/draw_tool.h"
#include "game/game_play/physics/game_board.h"
#include "game/game_play/physics/game_play_grid_matrix.h"
#include "game/game_play/tetromino/tetromino.h"
#include "game/game_play/ui/game_play_ui.h"
#include "simulate.h"
#include "game/game_play/game_play.h"

static void render_tetromino_at_r(const tetromino_t* t, wchar_t block_type, pos_t pos_x, pos_t pos_y)
{
    debug();

    my_assert(t != NULL);

    pthread_mutex_lock(&g_cursor_mutex);
    const tetromino_symbol_t* s = G_TETROMINO_SYMBOLS + t->symbol_id;
    const int x_offset = GAME_PLAY_BOARD_START_POS_X_IN_WPRINT;
    const int y_offset = GAME_PLAY_BOARD_START_POS_Y_IN_WPRINT - 1;
    for (int i = 0; i < s->height; ++i) {
        const block_t* row = s->grid[i];
        for (int j = 0; row[j]; ++j) {
            if (row[j] == BLOCK_T_FALSE) {
                continue;
            }
            pos_t block_pos_x_in_wprint = pos_x + i + x_offset;
            if (block_pos_x_in_wprint < GAME_PLAY_BOARD_START_POS_X_IN_WPRINT) {
                continue;
            }
            pos_t block_pos_y_in_wprint = 2 * (pos_y + j) + y_offset;
            wprintf_at(block_pos_x_in_wprint, block_pos_y_in_wprint, L"%lc", block_type);
        }
    }
    wdraw_newline();
    pthread_mutex_unlock(&g_cursor_mutex);
}

static void render_tetromino(const tetromino_t* t, wchar_t block_type)
{
    debug();

    render_tetromino_at_r(t, block_type, t->pos_x, t->pos_y);
}

void disappear_tetromino(const tetromino_t* t)
{
    debug();

    render_tetromino(t, BLOCK_WHITE_LARGE_SQUARE);
}

void draw_tetromino(const tetromino_t* t)
{
    debug();

    render_tetromino(t, t->block_code);
}

void draw_tetromino_at_r(const tetromino_t* t, pos_t pos_x, pos_t pos_y)
{
    debug();

    render_tetromino_at_r(t, t->block_code, pos_x, pos_y);
}

/* return tetromino's status */
int move_tetromino(tetromino_t* const out_t)
{
    debug();

    static const pos_t S_DX[] = { 1, 0, -1, 0 };
    static const pos_t S_DY[] = { 0, 1, 0, -1 };

    pos_t npos_x = out_t->pos_x + out_t->velocity * S_DX[out_t->dir];
    pos_t npos_y = out_t->pos_y + out_t->velocity * S_DY[out_t->dir];
    const tetromino_symbol_t* s = G_TETROMINO_SYMBOLS + out_t->symbol_id;
    for (int i = 0; i < s->height; ++i) {
        const block_t* row = s->grid[i];
        for (int j = 0; row[j]; ++j) {
            if (row[j] == BLOCK_T_FALSE) {
                continue;
            }
            pos_t cpos_x = npos_x + (pos_t)i;
            pos_t cpos_y = npos_y + (pos_t)j;
            my_assert(cpos_x >= GAME_PLAY_TETROMINO_POS_X_MIN);
            if (cpos_y < GAME_PLAY_TETROMINO_POS_Y_MIN || cpos_y > GAME_PLAY_TETROMINO_POS_Y_MAX) {
                ewprintf("hi1\n");
                return TETROMINO_STATUS_INPLACE;
            }
            if (cpos_x > GAME_PLAY_TETROMINO_POS_X_MAX) {
                ewprintf("hi2\n");
                return TETROMINO_STATUS_ON_OTHERBLOCK;
            }
            //my_assert(cpos_x >= 0 && cpos_x < GAME_PLAY_BOARD_HEIGHT);
            if (cpos_x < 0) {
                continue;
            }
            my_assert(cpos_x < GAME_PLAY_BOARD_HEIGHT);
            my_assert(cpos_y >= 0 && cpos_y < GAME_PLAY_BOARD_WIDTH);
            game_board_grid_element_t val = g_game_board.grid[cpos_x][cpos_y];
            if (val != GAME_PLAY_BOARD_GRID_ELEMENT_DEFAULT && val != out_t->id) {
                return TETROMINO_STATUS_ON_OTHERBLOCK;
            }
        }
    }
    out_t->pos_x = npos_x;
    out_t->pos_y = npos_y;
    ewprintf("(%d, %d)\n", out_t->pos_x, out_t->pos_y);
    ewprintf("hi4\n");
    return TETROMINO_STATUS_MOVED;
}

void petrity_tetromino(const tetromino_t* t)
{
    const tetromino_symbol_t* s = G_TETROMINO_SYMBOLS + t->symbol_id;
    for (int i = 0; i < s->height; ++i) {
        const block_t* row = s->grid[i];
        for (int j = 0; row[j]; ++j) {
            if (row[j] == BLOCK_T_FALSE) {
                continue;
            }
            pos_t pos_x = t->pos_x + i;
            pos_t pos_y = t->pos_y + j;
            g_game_board.grid[pos_x][pos_y] = t->id;
        }
    }
}

bool is_at_skyline(const tetromino_t* t)
{
    const tetromino_symbol_t* s = G_TETROMINO_SYMBOLS + t->symbol_id;
    return t->pos_x + s->height <= 0;
}
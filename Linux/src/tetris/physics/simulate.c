#include <stdio.h>

#include "debug.h"
#include "draw/cursor.h"
#include "draw/draw_tool.h"
#include "simulate.h"
#include "tetris/physics/tetris_play_board.h"
#include "tetris/scene/tetris_play_scene.h"
#include "tetris/tetris_play_submodule.h"

static void render_a_tetromino_at(const tetromino_t* tetro, wchar_t block_wprint, pos_t pos_x, pos_t pos_y)
{
    debug();

    my_assert(tetro != NULL);

    const tetromino_symbol_t* symbol = G_TETROMINO_SYMBOLS + tetro->symbol_id;
    const int x_wprint_offset = TETRIS_PLAY_BOARD_START_POS_X_WPRINT;
    const int y_wprint_offset = TETRIS_PLAY_BOARD_START_POS_Y_WPRINT - 1;
    for (int i = 0; i < symbol->height; ++i) {
        const block_t* row = symbol->block_matrix[i];
        for (int j = 0; row[j]; ++j) {
            if (row[j] == BLOCK_T_FALSE) {
                continue;
            }
            pos_t each_pos_x_wprint = pos_x + i + x_wprint_offset;
            if (each_pos_x_wprint < TETRIS_PLAY_BOARD_START_POS_X_WPRINT) {
                continue;
            }
            pos_t each_pos_y_wprint = 2 * (pos_y + j) + y_wprint_offset;
            wprintf_at(each_pos_x_wprint, each_pos_y_wprint, L"%lc", block_wprint);
        }
    }
    fflush(stdout);
}

static void render_a_tetromino_at_r(const tetromino_t* tetro, wchar_t block_wprint, pos_t pos_x, pos_t pos_y)
{
    debug();

    pthread_mutex_lock(&g_cursor_mtx);
    render_a_tetromino_at(tetro, block_wprint, pos_x, pos_y);
    pthread_mutex_unlock(&g_cursor_mtx);
}

static void render_a_tetromino_r(const tetromino_t* tetro, wchar_t block_wprint)
{
    debug();

    render_a_tetromino_at_r(tetro, block_wprint, tetro->pos_x, tetro->pos_y);
}

void erase_a_tetromino_r(const tetromino_t* tetro)
{
    debug();

    render_a_tetromino_r(tetro, BLOCK_WPRINT_WHITE_LARGE_SQUARE);
}

void draw_a_tetromino_r(const tetromino_t* tetro)
{
    debug();

    render_a_tetromino_r(tetro, tetro->block_code);
}

/* return tetromino's status when moving left, right, or down.
   implement the rotation operation separately. */
tetromino_status_t move_a_tetromino(game_board_t* const board, tetromino_t* const out_tetro)
{
    debug();

    static const pos_t S_DX[] = { 1, 0, -1, 0 };
    static const pos_t S_DY[] = { 0, 1, 0, -1 };

    pos_t npos_x = out_tetro->pos_x + out_tetro->velocity * S_DX[out_tetro->dir];
    pos_t npos_y = out_tetro->pos_y + out_tetro->velocity * S_DY[out_tetro->dir];
    const tetromino_symbol_t* symbol = G_TETROMINO_SYMBOLS + out_tetro->symbol_id;
    for (int i = 0; i < symbol->height; ++i) {
        const block_t* row = symbol->block_matrix[i];
        for (int j = 0; row[j]; ++j) {
            if (row[j] == BLOCK_T_FALSE) {
                continue;
            }
            pos_t each_npos_x = npos_x + (pos_t)i;
            pos_t each_npos_y = npos_y + (pos_t)j;
            my_assert(each_npos_x >= TETRIS_PLAY_TETROMINO_POS_X_MIN);
            if (each_npos_y < TETRIS_PLAY_TETROMINO_POS_Y_MIN || each_npos_y > TETRIS_PLAY_TETROMINO_POS_Y_MAX) {
                ewprintf("hi1\n");
                return TETROMINO_STATUS_INPLACE;
            }
            if (each_npos_x > TETRIS_PLAY_TETROMINO_POS_X_MAX) {
                ewprintf("hi2\n");
                return TETROMINO_STATUS_ONTHEGROUND;
            }
            if (each_npos_x < 0) {
                continue;
            }
            my_assert(each_npos_x >= 0);
            my_assert(each_npos_x < TETRIS_PLAY_BOARD_HEIGHT);
            my_assert(0 <= each_npos_y && each_npos_y < TETRIS_PLAY_BOARD_WIDTH);
            game_board_grid_element_t each_value = board->grid[each_npos_x][each_npos_y];
            if (each_value != TETRIS_PLAY_BOARD_GRID_ELEMENT_DEFAULT && each_value != out_tetro->id) {
                ewprintf("hi3\n");
                return TETROMINO_STATUS_ONTHEGROUND;
            }
        }
    }
    out_tetro->pos_x = npos_x;
    out_tetro->pos_y = npos_y;
    ewprintf("hi4\n");
    return TETROMINO_STATUS_MOVED;
}

void petrity_tetromino(game_board_t* const board, const tetromino_t* tetro)
{
    debug();

    const tetromino_symbol_t* symbol = G_TETROMINO_SYMBOLS + tetro->symbol_id;
    for (int i = 0; i < symbol->height; ++i) {
        const block_t* row = symbol->block_matrix[i];
        for (int j = 0; row[j]; ++j) {
            if (row[j] == BLOCK_T_FALSE) {
                continue;
            }
            pos_t each_pos_x = tetro->pos_x + i;
            pos_t each_pos_y = tetro->pos_y + j;
            if (each_pos_x < 0) {
                continue;
            }
            my_assert(each_pos_x >= 0);
            my_assert(each_pos_x < TETRIS_PLAY_BOARD_HEIGHT);
            my_assert(0 <= each_pos_y && each_pos_y < TETRIS_PLAY_BOARD_WIDTH);
            board->grid[each_pos_x][each_pos_y] = tetro->id;
        }
    }
}

bool is_at_skyline(const tetromino_t* tetro)
{
    debug();

    my_assert(0 <= tetro->symbol_id && tetro->symbol_id < TOTAL_TETROMINO_NUM_OF_KINDS);
    const tetromino_symbol_t* symbol = G_TETROMINO_SYMBOLS + tetro->symbol_id;
    return tetro->pos_x + symbol->height <= 0;
}
#include <stdio.h>

#include "debug.h"
#include "draw/draw_tool.h"
#include "tetris/play/tetris_play_update_world.h"
#include "tetris_play_renderer.h"
#include "tetris_play_scene.h"

static inline pos_t get_pos_wprint(pos_t pos)
{
    pos_t ret = { pos.x + TETRIS_PLAY_BOARD_POS_X_WPRINT, 2 * pos.y + TETRIS_PLAY_BOARD_POS_Y_WPRINT };
    return ret;
}

static inline void render_a_block(pos_t pos, wchar_t block_wprint)
{
    pos_t pos_wprint = get_pos_wprint(pos);
    if (pos_wprint.x < TETRIS_PLAY_BOARD_POS_X_WPRINT) {
        return;
    }
    wdraw_unit_matrix_at(block_wprint, (int)pos_wprint.x, (int)pos_wprint.y);
}

static void render_a_tetromino_at_wprint(const tetromino_t* tetro, wchar_t block_wprint, pos_t pos_wprint)
{
    debug();

    my_assert(tetro != NULL);

    tetromino_matrix_t symbol = get_tetromino_matrix(tetro->symbol_id, tetro->dir);
    tetromino_matrix_n_t n = get_tetromino_matrix_n(tetro->symbol_id);
    for (int idx = 0; idx < n * n; ++idx) {
        if (is_empty_block(symbol, idx)) {
            continue;
        }
        int i = idx / n;
        int j = idx % n;
        {
            pos_t each_pos_wprint = { pos_wprint.x + i, pos_wprint.y + 2 * j };
            wdraw_unit_matrix_at(block_wprint, (int)each_pos_wprint.x, (int)each_pos_wprint.y);
        }
    }
}

static inline void render_a_tetromino_at_wprint_r(const tetromino_t* tetro, wchar_t block_wprint, pos_t pos_wprint)
{
    cursor_lock();
    render_a_tetromino_at_wprint(tetro, block_wprint, pos_wprint);
    cursor_unlock();
}

static void render_a_tetromino_at(const tetromino_t* tetro, wchar_t block_wprint, pos_t pos)
{
    // debug();

    my_assert(tetro != NULL);

    // /* Invalid tetrominoes are not rendered. */
    // if (tetro->id == -1) {
    //     return;
    // }

    tetromino_matrix_t symbol = get_tetromino_matrix(tetro->symbol_id, tetro->dir);
    tetromino_matrix_n_t n = get_tetromino_matrix_n(tetro->symbol_id);
    for (int idx = 0; idx < n * n; ++idx) {
        if (is_empty_block(symbol, idx)) {
            continue;
        }
        int i = idx / n;
        int j = idx % n;
        {
            pos_t each_pos = { pos.x + i, pos.y + j };
            render_a_block(each_pos, block_wprint);
        }
    }
}

static void render_a_tetromino_at_r(const tetromino_t* tetro, wchar_t block_wprint, pos_t pos)
{
    cursor_lock();
    render_a_tetromino_at(tetro, block_wprint, pos);
    cursor_unlock();
}

static void render_a_tetromino_r(const tetromino_t* tetro, wchar_t block_wprint, wchar_t ground_pos_wprint)
{
    (void)ground_pos_wprint;
    // render_a_tetromino_at_r(tetro, ground_pos_wprint, tetro->ground_pos);
    render_a_tetromino_at_r(tetro, block_wprint, tetro->pos);
}

// static void erase_a_tetromino_r(const tetromino_t* tetro)
// {
//     render_a_tetromino_r(tetro, BLOCK_WPRINT_WHITE_LARGE_SQUARE, BLOCK_WPRINT_WHITE_LARGE_SQUARE);
// }

static void draw_a_tetromino_r(const tetromino_t* tetro)
{
    render_a_tetromino_r(tetro, (wchar_t)tetro->block.wprint, BLOCK_WPRINT_LIGHT_LARGE_SQUARE);
}

static void render_tetromino_manager_out(tetromino_manager_t* const out_tetro_man)
{
    draw_a_tetromino_r(out_tetro_man->tetro_main);
}

void render_out(tetris_play_manager_t* const out_man)
{
    debug();

    // erase_a_tetromino_r(&out_play_manager->prev_tetromino);
    // draw_a_tetromino_r(&out_play_manager->tetromino);
    render_tetromino_manager_out(&out_man->tetro_man);
    fflush(stdout);
}

void wdraw_a_tetromino_at_wprint_r(const tetromino_t* tetro, pos_t pos_wprint)
{
    render_a_tetromino_at_wprint_r(tetro, (wchar_t)tetro->block.wprint, pos_wprint);
}
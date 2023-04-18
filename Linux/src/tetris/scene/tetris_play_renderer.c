#include <stdio.h>

#include "debug.h"
#include "draw/draw_tool.h"
#include "fixed_queue.h"
#include "tetris/object/pos.h"
#include "tetris/play/tetris_play_update_world.h"
#include "tetris_play_renderer.h"
#include "tetris_play_scene.h"

static inline pos_t get_pos_wprint(pos_t pos)
{
    pos_t ret = { pos.x + 0, 2 * pos.y + 1 };
    return ret;
}

static void render_a_tetromino_poswprint(const tetromino_t* tetro, pos_t pos_wprint)
{
    debug();

    cursor_lock();

    my_assert(tetro != NULL);

    tetromino_matrix_t symbol = get_tetromino_matrix(tetro->symbol_id, tetro->dir);
    tetromino_matrix_n_t n = get_tetromino_matrix_n(tetro->symbol_id);

    if (tetro->block.wprint == BLOCK_WPRINT_EMPTY) {
        for (int idx = 0; idx < n * n; ++idx) {
            if (is_empty_block(symbol, idx)) {
                continue;
            }
            int i = idx / n;
            int j = idx % n;
            {
                static wchar_t buf[3];
                buf[0] = buf[1] = tetro->block.wprint;
                buf[2] = L'\0';
                pos_t each_pos_wprint = { pos_wprint.x + i, pos_wprint.y + 2 * j };
                wdraw_row_at(buf, each_pos_wprint.x, each_pos_wprint.y);
            }
        }
    } else {
        for (int idx = 0; idx < n * n; ++idx) {
            if (is_empty_block(symbol, idx)) {
                continue;
            }
            int i = idx / n;
            int j = idx % n;
            {
                pos_t each_pos_wprint = { pos_wprint.x + i, pos_wprint.y + 2 * j };
                wdraw_unit_matrix_at(tetro->block.wprint, (int)each_pos_wprint.x, (int)each_pos_wprint.y);
            }
        }
    }

    cursor_unlock();
}

static void callback_render_tetromino_manager_out(void* const out_void, int i, void* arg)
{
    (void)i;
    (void)arg;
    tetromino_t* tetro = (tetromino_t*)out_void;
    wdraw_a_tetromino_cleanblock(tetro, BLOCK_WPRINT_EMPTY);
}

void wdraw_a_tetromino_cleanblock(tetromino_t* const out_tetro, block_wprint_t cleanblock)
{
    debug();

    if (!is_first_drawn_tetromino(out_tetro)) {
        render_a_tetromino_poswprint(out_tetro->prev_drawn, out_tetro->prev_drawn->pos_wprint);
    }
    render_a_tetromino_poswprint(out_tetro, out_tetro->pos_wprint);
    save_tetromino_tobedrawn(out_tetro, cleanblock);
}

static void render_tetromino_manager_out(tetromino_manager_t* const out_man)
{
    if (out_man->tetro_main == NULL) {
        return;
    }
    wdraw_a_tetromino_cleanblock(out_man->tetro_main, BLOCK_WPRINT_WHITE_LARGE_SQUARE);
    traverse_queue(&out_man->que, callback_render_tetromino_manager_out, NULL);
}

static void render_a_skyline(const board_t* board)
{
    debug();

    int i = TETRIS_PLAY_SKYLINE_POS_X - TETRIS_PLAY_BOARD_POS_X;
    my_assert(1 <= i && i <= board->height - 2);
    cursor_lock();
    wgotoxy((int)board->pos_wprint.x + i, (int)board->pos_wprint.y);
    for (int step = 0; step < 1; ++step) {
        static wchar_t buf[TETRIS_PLAY_BOARD_WIDTH + 1];
        for (int j = 0; j < board->width; ++j) {
            buf[j] = board->grid[i + step][j].wprint;
        }
        buf[board->width] = L'\0';
        wdraw_row_newline(buf, board->width_wprint);
    }
    cursor_unlock();
}

void render_out(tetris_play_manager_t* const out_man)
{
    debug();

    my_assert(out_man != NULL);

    if (out_man->status != TETRIS_PLAY_STATUS_GAMEOVER) {
        render_tetromino_manager_out(&out_man->tetro_man);
        render_a_skyline(&out_man->board);
    } else {
        ewprintf("render_out(): out_man->status = TETRIS_PLAY_STATUS_GAMEOVER, so do nothing.\n");
    }
    fflush(stdout);
}

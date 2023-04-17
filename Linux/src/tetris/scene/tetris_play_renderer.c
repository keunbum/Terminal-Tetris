#include <stdio.h>

#include "debug.h"
#include "draw/draw_tool.h"
#include "fixed_queue.h"
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
    out_man->tetro_main->pos_wprint = get_pos_wprint(out_man->tetro_main->pos);
    wdraw_a_tetromino_cleanblock(out_man->tetro_main, BLOCK_WPRINT_WHITE_LARGE_SQUARE);
    traverse_queue(&out_man->que, callback_render_tetromino_manager_out, NULL);
}

void render_out(tetris_play_manager_t* const out_man)
{
    debug();

    my_assert(out_man != NULL);

    render_tetromino_manager_out(&out_man->tetro_man);
    fflush(stdout);
}

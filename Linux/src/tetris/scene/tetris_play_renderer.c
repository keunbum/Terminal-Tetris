#include <stdio.h>

#include "debug.h"
#include "draw/draw_tool.h"
#include "fixed_queue.h"
#include "tetris/object/pos.h"
#include "tetris/play/tetris_play_update_world.h"
#include "tetris_play_renderer.h"
#include "tetris_play_scene.h"

static void render_a_tetromino_poswprint(const tetromino_t* tetro, pos_int_t pos_wprint)
{
    debug();

    cursor_lock();
    my_assert(tetro != NULL);
    tetromino_symbol_t symbol = get_tetromino_symbol(tetro->symbol_id, tetro->dir);
    if (tetro->block.wprint == BLOCK_WPRINT_EMPTY) {
        traverse_symbol(i, j, symbol) {
            static wchar_t buf[3];
            buf[0] = buf[1] = tetro->block.wprint;
            buf[2] = L'\0';
            wdraw_row_at(buf, pos_wprint.x + i, pos_wprint.y + 2 * j);
        }
    } else {
        traverse_symbol(i, j, symbol) {
            wdraw_unit_matrix_at(tetro->block.wprint, pos_wprint.x + i, pos_wprint.y + 2 * j);
        }
    }
    cursor_unlock();
}

static void callback_render_tetromino_manager_out(void* const out_void, int i, void* arg)
{
    (void)i;
    (void)arg;
    wdraw_a_tetromino((tetromino_t*)out_void);
}

void wdraw_a_tetromino(tetromino_t* const out_tetro)
{
    debug();

    if (!is_valid_tetromino(out_tetro)) {
        return;
    }
    if (!is_first_drawn_tetromino(out_tetro)) {
        render_a_tetromino_poswprint(out_tetro->prev_drawn, get_posint(out_tetro->prev_drawn->pos_wprint));
    }
    render_a_tetromino_poswprint(out_tetro, get_posint(out_tetro->pos_wprint));
    save_tetromino_tobedrawn(out_tetro);
}

static void render_tetromino_manager_out(tetromino_manager_t* const out_man)
{
    wdraw_a_tetromino(out_man->tetro_main);
    wdraw_a_tetromino(out_man->tetro_hold);
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

    my_assert(is_valid_tetromino(out_man));

    if (out_man->status != TETRIS_PLAY_STATUS_GAMEOVER) {
        render_tetromino_manager_out(&out_man->tetro_man);
        render_a_skyline(&out_man->board);
    } else {
        ewprintf("render_out(): out_man->status = TETRIS_PLAY_STATUS_GAMEOVER, so do nothing.\n");
    }
    fflush(stdout);
}

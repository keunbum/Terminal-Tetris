#include <stdio.h>

#include "debug.h"
#include "draw/draw_tool.h"
#include "fixed_queue.h"
#include "tetris/object/pos.h"
#include "tetris/play/tetris_play_update_gameplay.h"
#include "tetris_play_renderer.h"
#include "tetris_play_scene.h"
#include "tetris/play/tetris_play_ghost_piece.h"

static void render_a_tetromino_poswprint_r(const tetromino_t* tetro, pos_int_t pos_wprint)
{
    cursor_lock();
    tetromino_shape_t shape = get_tetromino_shape(tetro->shape_id, tetro->dir);
    if (tetro->block.wprint == BLOCK_WPRINT_EMPTY) {
        traverse_shape(i, j, shape) {
            static wchar_t s_buf[3] = {BLOCK_WPRINT_EMPTY, BLOCK_WPRINT_EMPTY, L'\0'};
            wdraw_row_at(s_buf, pos_wprint.x + i, pos_wprint.y + 2 * j);
        }
    } else {
        traverse_shape(i, j, shape) {
            wdraw_unit_matrix_at(tetro->block.wprint, pos_wprint.x + i, pos_wprint.y + 2 * j);
        }
    }
    cursor_unlock();
}

static void callback_wdraw_a_tetromino(void* const out_void, int i, void* arg)
{
    (void)i;
    (void)arg;
    wdraw_a_tetromino((tetromino_t*)out_void);
}

static void render_tetromino_manager_out(tetromino_manager_t* const out_man)
{
    wdraw_a_tetromino_with_ghost_piece(out_man->tetromino_in_play, &out_man->ghost_piece, &out_man->matrix);
    wdraw_a_tetromino(out_man->tetromino_hold);
    traverse_queue(&out_man->next_queue, callback_wdraw_a_tetromino, NULL);
}

static void render_a_skyline_r(const matrix_t* matrix)
{
    int i = TETRIS_PLAY_SKYLINE_POS_X - TETRIS_PLAY_MATRIX_POS_X;
    cursor_lock();
    wgotoxy(matrix->pos_wprint.x + i, matrix->pos_wprint.y);
    static wchar_t s_buf[TETRIS_PLAY_MATRIX_WIDTH + 1];
    for (int j = 0; j < matrix->width; ++j) {
        s_buf[j] = matrix->grid[i][j].wprint;
    }
    s_buf[matrix->width] = L'\0';
    wdraw_row_newline(s_buf, matrix->width_wprint);
    cursor_unlock();
}

void wdraw_a_tetromino(tetromino_t* const out_tetro)
{
    if (!is_valid_tetromino(out_tetro)) {
        return;
    }
    if (!is_first_drawn_tetromino(out_tetro)) {
        render_a_tetromino_poswprint_r(out_tetro->prev_drawn, get_posint(out_tetro->prev_drawn->pos_wprint));
    }
    render_a_tetromino_poswprint_r(out_tetro, get_posint(out_tetro->pos_wprint));
    save_tetromino_tobedrawn(out_tetro);
}

void wdraw_a_tetromino_with_ghost_piece(tetromino_t* const out_tetro, tetromino_t* const out_ghost_piece, const matrix_t* matrix)
{
    update_ghost_piece_dir_pos(out_ghost_piece, out_tetro, matrix);
    wdraw_a_tetromino(out_ghost_piece);
    wdraw_a_tetromino(out_tetro);
}

void render_out(tetris_play_manager_t* const out_man)
{
    render_tetromino_manager_out(&out_man->tetro_man);
    render_a_skyline_r(&out_man->tetro_man.matrix);
    fflush(stdout);
}

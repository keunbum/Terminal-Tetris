#include "tetris_play_tetromino_statistic.h"
#include "draw/draw_tool.h"
#include "tetris/object/tetromino.h"
#include "tetris/scene/tetris_play_renderer.h"
#include "tetris/object/matrix.h"

#define TETRIS_PLAY_STATISTIC_FRAME_HEIGHT (3 * TETROMINO_NUM_OF_KINDS + 2)
#define TETRIS_PLAY_STATISTIC_FRAME_WIDTH (16)

static inline void wdraw_tetromino_spawned_cnt(const tetris_play_statistic_t* st, shape_id_t id)
{
    const int pos_x_wprint = st->tetromino_pos_wprint.x + (id + 1) * st->interval_height;
    const int pos_y_wprint = st->tetromino_pos_wprint.y;
    wprintf_at_r(pos_x_wprint + 1 + 0, pos_y_wprint + 11, L"%d", st->tetromino_spawned_cnts[id]);
}

static inline void wdraw_cleared_lines(const tetris_play_statistic_t* st)
{
    const int pos_x_wprint = LINES_DRAW_POS_X_WPRINT;
    const int pos_y_wprint = LINES_DRAW_POS_Y_WPRINT;
    wprintf_at_r(pos_x_wprint, pos_y_wprint, L"LINES: %-4d", st->tetromino_cleared_lines);
}

static void wdraw_tetris_play_statistics_tetrominos(const tetris_play_statistic_t* st)
{
    for (shape_id_t i = 0; i < TETROMINO_NUM_OF_KINDS; ++i) {
        wdraw_a_tetromino(st->tetrominos[i]);
        wdraw_tetromino_spawned_cnt(st, i);
    }
}

void init_tetris_play_statistics_malloc(tetris_play_statistic_t* const out_stat)
{
    out_stat->pos_wprint = create_posint(TETRIS_PLAY_STATISTIC_POS_X_WPRINT, TETRIS_PLAY_STATISTIC_POS_Y_WPRINT);
    out_stat->tetromino_pos_wprint = create_posint(TETRIS_PLAY_STATISTIC_TETROMINO_POS_X_WPRINT, TETRIS_PLAY_STATISTIC_TETROMINO_POS_Y_WPRINT);
    out_stat->interval_height = TETRIS_PLAY_STATISTIC_INTERVAL_HEIGHT;
    out_stat->tetromino_cleared_lines = 0;

    for (shape_id_t shape_id = 0; shape_id < TETROMINO_NUM_OF_KINDS; ++shape_id) {
        static const int S_TETRO_X_CORRECTION[TETROMINO_NUM_OF_KINDS] = { +0, -1, +0, +0, +0, +0, +0 };
        const int each_pos_x_wprint = out_stat->tetromino_pos_wprint.x + (shape_id + 1) * out_stat->interval_height + S_TETRO_X_CORRECTION[shape_id];
        const int each_pos_y_wprint = out_stat->tetromino_pos_wprint.y + 1;
        pos_t pos_wprint = { (pos_e_t)each_pos_x_wprint, (pos_e_t)each_pos_y_wprint };
        out_stat->tetrominos[shape_id] = create_tetromino_shape_poswprint_malloc(shape_id, pos_wprint, BLOCK_WPRINT_EMPTY);
    }

    for (int i = 0; i < TETROMINO_NUM_OF_KINDS; ++i) {
        out_stat->tetromino_spawned_cnts[i] = 0;
    }

    init_frame(&out_stat->frame,
        TETRIS_PLAY_STATISTIC_FRAME_HEIGHT, TETRIS_PLAY_STATISTIC_FRAME_WIDTH,
        out_stat->pos_wprint,
        L"STATISTICS",
        UNIT_MATRIX_HOR_LINE,
        UNIT_MATRIX_VER_LINE,
        UNIT_MATRIX_CORNER_TOP_LEFT,
        UNIT_MATRIX_CORNER_TOP_RIGHT,
        UNIT_MATRIX_CORNER_BOT_LEFT,
        UNIT_MATRIX_CORNER_BOT_RIGHT);
}

void cleanup_tetris_play_statistics_free(tetris_play_statistic_t* const out_stat)
{
    cleanup_frame(&out_stat->frame);
    for (shape_id_t shape_id = 0; shape_id < TETROMINO_NUM_OF_KINDS; ++shape_id) {
        cleanup_tetromino_free(out_stat->tetrominos[shape_id]);
    }    
}

void wdraw_tetris_play_statistics(const tetris_play_statistic_t* st)
{
    wdraw_frame(&st->frame, 3);
    wdraw_tetris_play_statistics_tetrominos(st);
    wdraw_cleared_lines(st);
}

void inc_tetromino_cnt(tetris_play_statistic_t* const out_stat, shape_id_t id)
{
    out_stat->tetromino_spawned_cnts[id] += 1;
    wdraw_tetromino_spawned_cnt(out_stat, id);
}

void inc_cleared_lines(tetris_play_statistic_t* const out_stat, int by)
{
    out_stat->tetromino_cleared_lines += by;
    wdraw_cleared_lines(out_stat);
}
#include "tetris_play_tetromino_statistic.h"
#include "draw/draw_tool.h"
#include "tetris/object/tetromino.h"
#include "tetris/scene/tetris_play_renderer.h"

#define TETRIS_PLAY_STATISTIC_FRAME_HEIGHT (3 * TETROMINO_NUM_OF_KINDS + 2)
#define TETRIS_PLAY_STATISTIC_FRAME_WIDTH (16)

static void wdraw_tetromino_spawned_cnt(const tetris_play_statistic_t* st, symbol_id_t id)
{
    debug();

    my_assert(st != NULL);

    const int pos_x_wprint = (int)st->tetromino_pos_wprint.x + (id + 1) * st->interval_height;
    const int pos_y_wprint = (int)st->tetromino_pos_wprint.y;
    wprintf_at_r(pos_x_wprint + 1 + 0, pos_y_wprint + 11, L"%d", st->tetromino_spawned_cnts[id]);
}

static void wdraw_tetris_play_statistics_tetrominos(const tetris_play_statistic_t* st)
{
    debug();

    my_assert(st != NULL);

    for (symbol_id_t i = 0; i < TETROMINO_NUM_OF_KINDS; ++i) {
        wdraw_a_tetromino_cleanblock(st->tetrominos[i], BLOCK_WPRINT_EMPTY);
        wdraw_tetromino_spawned_cnt(st, i);
    }
}

void init_tetris_play_statistics(tetris_play_statistic_t* const out_stat, tetromino_generator_t* const out_gen)
{
    debug();
    
    out_stat->pos_wprint = create_pos(TETRIS_PLAY_STATISTIC_POS_X_WPRINT, TETRIS_PLAY_STATISTIC_POS_Y_WPRINT);
    out_stat->tetromino_pos_wprint = create_pos(TETRIS_PLAY_STATISTIC_TETROMINO_POS_X_WPRINT, TETRIS_PLAY_STATISTIC_TETROMINO_POS_Y_WPRINT);
    out_stat->interval_height = TETRIS_PLAY_STATISTIC_INTERVAL_HEIGHT;

    for (symbol_id_t symbol_id = 0; symbol_id < TETROMINO_NUM_OF_KINDS; ++symbol_id) {
        static const int S_TETRO_X_CORRECTION[TETROMINO_NUM_OF_KINDS] = { +0, +0, +0, -1, -1, -1, -1 };
        const tetromino_matrix_n_t n = get_tetromino_matrix_n(symbol_id);
        const int each_pos_x_wprint = (int)out_stat->tetromino_pos_wprint.x + (symbol_id + 1) * out_stat->interval_height;
        const int each_pos_y_wprint = (int)out_stat->tetromino_pos_wprint.y + 4 - n;
        pos_t pos_wprint = { each_pos_x_wprint + S_TETRO_X_CORRECTION[symbol_id], each_pos_y_wprint };
        out_stat->tetrominos[symbol_id] = create_tetromino_symbol_poswprint_malloc(out_gen, symbol_id, pos_wprint);
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

void wdraw_tetris_play_statistics(const tetris_play_statistic_t* st)
{
    debug();

    my_assert(st != NULL);

    wdraw_frame(&st->frame, 3);
    wdraw_tetris_play_statistics_tetrominos(st);
}

void inc_tetromino_cnt(tetris_play_statistic_t* const out_stat, symbol_id_t id)
{
    out_stat->tetromino_spawned_cnts[id] += 1;
    wdraw_tetromino_spawned_cnt(out_stat, id);
}
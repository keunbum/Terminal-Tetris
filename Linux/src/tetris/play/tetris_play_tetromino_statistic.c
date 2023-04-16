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

static void wdraw_tetris_play_statistics_tetrominos(const tetris_play_statistic_t* st, const block_wprint_set_t* set)
{
    debug();

    my_assert(st != NULL);
    my_assert(set != NULL);

    static const int S_TETRO_X_CORRECTION[TETROMINO_NUM_OF_KINDS] = { +0, +0, +0, -1, -1, -1, -1 };

    for (symbol_id_t s = 0; s < TETROMINO_NUM_OF_KINDS; ++s) {
        tetromino_t t;
        t.symbol_id = s;
        t.dir = TETROMINO_INIT_DIR;
        t.block.wprint = set->wprint_values[t.symbol_id];
        const tetromino_matrix_n_t n = get_tetromino_matrix_n(t.symbol_id);
        const int each_pos_x_wprint = (int)st->tetromino_pos_wprint.x + (s + 1) * st->interval_height;
        const int each_pos_y_wprint = (int)st->tetromino_pos_wprint.y + 4 - n;
        pos_t each_pos_wprint = { each_pos_x_wprint + S_TETRO_X_CORRECTION[s], each_pos_y_wprint };
        wdraw_a_tetromino_at_wprint_r(&t, each_pos_wprint);
        wdraw_tetromino_spawned_cnt(st, s);
    }
}

void init_tetris_play_statistics(tetris_play_statistic_t* const out_stat)
{
    debug();
    set_pos(&out_stat->pos_wprint, TETRIS_PLAY_STATISTIC_POS_X_WPRINT, TETRIS_PLAY_STATISTIC_POS_Y_WPRINT);
    set_pos(&out_stat->tetromino_pos_wprint, TETRIS_PLAY_STATISTIC_TETROMINO_POS_X_WPRINT, TETRIS_PLAY_STATISTIC_TETROMINO_POS_Y_WPRINT);
    out_stat->interval_height = TETRIS_PLAY_STATISTIC_INTERVAL_HEIGHT;

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

    for (int i = 0; i < TETROMINO_NUM_OF_KINDS; ++i) {
        out_stat->tetromino_spawned_cnts[i] = 0;
    }
}

void wdraw_tetris_play_statistics(const tetris_play_statistic_t* st, const block_wprint_set_t* set)
{
    debug();

    my_assert(st != NULL);
    my_assert(set != NULL);

    wdraw_frame(&st->frame, 3);
    wdraw_tetris_play_statistics_tetrominos(st, set);
}

void inc_tetromino_cnt_by_one(tetris_play_statistic_t* const out_stat, symbol_id_t id)
{
    out_stat->tetromino_spawned_cnts[id] += 1;
    wdraw_tetromino_spawned_cnt(out_stat, id);
}
#include "tetris_play_statistic.h"
// #include "draw/cursor.h"
#include "draw/draw_tool.h"
// #include "tetris/object/block.h"
#include "tetris/object/tetromino.h"
#include "tetris/scene/tetris_play_renderer.h"
#include "tetris/scene/tetris_play_screen.h"

// static size_t g_s_tetromino_spawned_cnt[TOTAL_TETROMINO_NUM_OF_KINDS];

// static void wdraw_tetromino_spawned_cnt(symbol_id_t id)
// {
//     const int pos_x_wprint = TETRIS_PLAY_STATISTIC_POS_X_WPRINT + (id + 1) * TETRIS_PLAY_STATISTIC_INTERVAL_HEIGHT - 2;
//     const int pos_y_wprint = TETRIS_PLAY_STATISTIC_TETROMINO_POS_Y_WPRINT;
//     wprintf_at_r(pos_x_wprint + 1 + 0, pos_y_wprint + 11, L"%d", g_s_tetromino_spawned_cnt[id]);
// }

static void new_wdraw_tetromino_spawned_cnt(const tetris_play_statistic_t* st, symbol_id_t id)
{
    debug();

    my_assert(st != NULL);

    const int pos_x_wprint = (int)st->tetromino_pos_wprint.x + (id + 1) * st->interval_height;
    const int pos_y_wprint = (int)st->tetromino_pos_wprint.y;
    wprintf_at_r(pos_x_wprint + 1 + 0, pos_y_wprint + 11, L"%d", st->tetromino_spawned_cnts[id]);
}

// static void wdraw_tetris_play_statistics_tetrominos(void)
// {
//     for (symbol_id_t s = 0; s < TOTAL_TETROMINO_NUM_OF_KINDS; ++s) {
//         tetromino_t t;
//         t.symbol_id = s;
//         t.dir = DIR_BOT;
//         t.block = G_BLOCK_CODE_SET->wprint_values[t.symbol_id];
//         const tetromino_matrix_n_t n = get_tetromino_matrix_n(t.symbol_id);
//         const int pos_x_wprint = TETRIS_PLAY_STATISTIC_POS_X_WPRINT + (s + 1) * TETRIS_PLAY_STATISTIC_INTERVAL_HEIGHT - 2;
//         const int pos_y_wprint = TETRIS_PLAY_STATISTIC_TETROMINO_POS_Y_WPRINT + 4 - n;
//         pos_t pos_wprint = { pos_x_wprint, pos_y_wprint };
//         draw_a_tetromino_at_wprint_r(&t, pos_wprint);
//         wdraw_tetromino_spawned_cnt(s);
//     }
// }

static void new_wdraw_tetris_play_statistics_tetrominos(const tetris_play_statistic_t* st, const block_wprint_set_t* set)
{
    debug();

    my_assert(st != NULL);
    my_assert(set != NULL);

    static const int S_TETRO_X_CORRECTION[TOTAL_TETROMINO_NUM_OF_KINDS] = { +0, +0, +0, -1, -1, -1, -1 };

    for (symbol_id_t s = 0; s < TOTAL_TETROMINO_NUM_OF_KINDS; ++s) {
        ewprintf("s: %d\n", s);
        tetromino_t t;
        t.symbol_id = s;
        t.dir = TETROMINO_INIT_DIR;
        my_assert(t.symbol_id < set->size);
        t.block.wprint = set->wprint_values[t.symbol_id];
        const tetromino_matrix_n_t n = get_tetromino_matrix_n(t.symbol_id);
        const int each_pos_x_wprint = (int)st->tetromino_pos_wprint.x + (s + 1) * st->interval_height;
        const int each_pos_y_wprint = (int)st->tetromino_pos_wprint.y + 4 - n;
        my_assert(s < TOTAL_TETROMINO_NUM_OF_KINDS);
        pos_t each_pos_wprint = { each_pos_x_wprint + S_TETRO_X_CORRECTION[s], each_pos_y_wprint };
        ewprintf("HI!\n");
        draw_a_tetromino_at_wprint_r(&t, each_pos_wprint);
        new_wdraw_tetromino_spawned_cnt(st, s);
    }
}

// static void init_tetris_play_statistics(void)
// {
//     debug();

//     for (int i = 0; i < TOTAL_TETROMINO_NUM_OF_KINDS; ++i) {
//         g_s_tetromino_spawned_cnt[i] = 0;
//     }
// }

void new_init_tetris_play_statistics(tetris_play_statistic_t* const out_st)
{
    debug();

    for (int i = 0; i < TOTAL_TETROMINO_NUM_OF_KINDS; ++i) {
        out_st->tetromino_spawned_cnts[i] = 0;
    }
}

// void wdraw_tetris_play_statistics_frame(void)
// {
//     init_tetris_play_statistics();
//     wprintf_at_r(TETRIS_PLAY_STATISTIC_POS_X_WPRINT, TETRIS_PLAY_STATISTIC_POS_Y_WPRINT, L"STATISTICS");
//     wdraw_tetris_play_statistics_tetrominos();
// }

void wdraw_tetris_play_statistics(const tetris_play_statistic_t* st, const block_wprint_set_t* set)
{
    debug();

    my_assert(st != NULL);
    my_assert(set != NULL);
    
    // new_init_tetris_play_statistics(out_st);
    wprintf_at_r((int)st->pos_wprint.x, (int)st->pos_wprint.y, L"STATISTICS");
    new_wdraw_tetris_play_statistics_tetrominos(st, set);
}

// void inc_tetromino_cnt_by_one(symbol_id_t id)
// {
//     g_s_tetromino_spawned_cnt[id] += 1;
//     wdraw_tetromino_spawned_cnt(id);
// }

void new_inc_tetromino_cnt_by_one(tetris_play_statistic_t* const out_st, symbol_id_t id)
{
    out_st->tetromino_spawned_cnts[id] += 1;
    new_wdraw_tetromino_spawned_cnt(out_st, id);
}
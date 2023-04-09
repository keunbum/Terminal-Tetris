#include "tetris_play_statistic.h"
#include "draw/draw_tool.h"
#include "tetris/scene/renderer.h"
#include "tetris/scene/tetris_play_screen.h"
#include "tetris/tetromino/block_code_set.h"
#include "tetris/tetromino/tetromino.h"

#define TETRIS_PLAY_STATISTIC_START_POS_X_WPRINT (TETRIS_PLAY_SINGLE_SCREEN_START_POS_X_WPRINT + 9)
#define TETRIS_PLAY_STATISTIC_START_POS_Y_WPRINT (TETRIS_PLAY_SINGLE_SCREEN_START_POS_Y_WPRINT + 5)

#define TETRIS_PLAY_STATISTIC_TETROMINO_START_POS_Y_WPRINT (TETRIS_PLAY_STATISTIC_START_POS_Y_WPRINT - 1)

#define TETRIS_PLAY_STATISTIC_INTERVAL_HEIGHT (3)

static size_t g_s_tetromino_spawned_cnt[TOTAL_TETROMINO_NUM_OF_KINDS];

static void wdraw_tetromino_spawned_cnt(symbol_id_t id)
{
    const int pos_x_wprint = TETRIS_PLAY_STATISTIC_START_POS_X_WPRINT + (id + 1) * TETRIS_PLAY_STATISTIC_INTERVAL_HEIGHT - 2;
    const int pos_y_wprint = TETRIS_PLAY_STATISTIC_TETROMINO_START_POS_Y_WPRINT;
    wprintf_at(pos_x_wprint + 1 + 0, pos_y_wprint + 11, L"%d", g_s_tetromino_spawned_cnt[id]);
}

static void wdraw_tetris_play_statistics_tetrominos(void)
{

    for (symbol_id_t s = 0; s < TOTAL_TETROMINO_NUM_OF_KINDS; ++s) {
        tetromino_t t;
        t.symbol_id = s;
        t.rotate_dir = DIR_BOT;
        t.block_code = G_BLOCK_CODE_SET->codes[t.symbol_id];
        const int pos_x_wprint = TETRIS_PLAY_STATISTIC_START_POS_X_WPRINT + (s + 1) * TETRIS_PLAY_STATISTIC_INTERVAL_HEIGHT - 2;
        const int pos_y_wprint = TETRIS_PLAY_STATISTIC_TETROMINO_START_POS_Y_WPRINT;
        pos_t pos_wprint = { pos_x_wprint, pos_y_wprint };
        draw_a_tetromino_mainbody_at_wprint_r(&t, pos_wprint);
        wdraw_tetromino_spawned_cnt(s);
    }
}

static void init_tetris_play_statistics(void)
{
    for (int i = 0; i < TOTAL_TETROMINO_NUM_OF_KINDS; ++i) {
        g_s_tetromino_spawned_cnt[i] = 0;
    }
}

void wdraw_tetris_play_statistics_frame(void)
{
    init_tetris_play_statistics();
    wprintf_at_r(TETRIS_PLAY_STATISTIC_START_POS_X_WPRINT, TETRIS_PLAY_STATISTIC_START_POS_Y_WPRINT, L"STATISTICS");
    wdraw_tetris_play_statistics_tetrominos();
}

void inc_tetromino_cnt_by_one(symbol_id_t id)
{
    g_s_tetromino_spawned_cnt[id] += 1;
    wdraw_tetromino_spawned_cnt(id);
}
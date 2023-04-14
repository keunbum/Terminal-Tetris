#ifndef __TETRIS_PLAY_STATISTIC__H
#define __TETRIS_PLAY_STATISTIC__H

#include "tetris/object/tetromino.h"

typedef struct {
    const pos_t pos;
    const pos_t pos_wprint;
    const pos_t tetromino_pos_wprint;
    const int interval_height;

    updatable_func_t update;
    drawable_func_t draw;

    size_t tetromino_spawned_cnts[TOTAL_TETROMINO_NUM_OF_KINDS];
} tetris_play_statistic_t;

#define TETRIS_PLAY_STATISTIC_POS_X (TETRIS_PLAY_SINGLE_SCREEN_POS_X + 8)
#define TETRIS_PLAY_STATISTIC_POS_Y (TETRIS_PLAY_SINGLE_SCREEN_POS_Y + 5)

#define TETRIS_PLAY_STATISTIC_POS_X_WPRINT TETRIS_PLAY_STATISTIC_POS_X
#define TETRIS_PLAY_STATISTIC_POS_Y_WPRINT TETRIS_PLAY_STATISTIC_POS_Y

#define TETRIS_PLAY_STATISTIC_INTERVAL_HEIGHT (3)

#define TETRIS_PLAY_STATISTIC_TETROMINO_POS_X_WPRINT (TETRIS_PLAY_STATISTIC_POS_X_WPRINT - TETRIS_PLAY_STATISTIC_INTERVAL_HEIGHT + 1)
#define TETRIS_PLAY_STATISTIC_TETROMINO_POS_Y_WPRINT (TETRIS_PLAY_STATISTIC_POS_Y_WPRINT - 1)


// void wdraw_tetris_play_statistics_frame(void);
// void inc_tetromino_cnt_by_one(symbol_id_t);

void new_init_tetris_play_statistics(tetris_play_statistic_t* const out_st);
void wdraw_tetris_play_statistics(const tetris_play_statistic_t* st);
void new_inc_tetromino_cnt_by_one(tetris_play_statistic_t* const out_st, symbol_id_t id);

#endif /* __TETRIS_PLAY_STATISTIC__H */
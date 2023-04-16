#ifndef __TETRIS_PLAY_TETROMINO_STATISTIC__H
#define __TETRIS_PLAY_TETROMINO_STATISTIC__H

#include "tetris/object/block_wprint_set.h"
#include "tetris/object/tetromino.h"
#include "tetris/object/frame.h"

typedef struct {
    pos_t pos_wprint;

    pos_t tetromino_pos_wprint;
    int interval_height;

    frame_t frame;

    // updatable_func_t update;
    // drawable_func_t draw;

    size_t tetromino_spawned_cnts[TETROMINO_NUM_OF_KINDS];
} tetris_play_statistic_t;

// #define TETRIS_PLAY_STATISTIC_POS_X (TETRIS_PLAY_BOARD_POS_X + 5)
// #define TETRIS_PLAY_STATISTIC_POS_Y (TETRIS_PLAY_SINGLE_SCREEN_POS_Y + 5)

#define TETRIS_PLAY_STATISTIC_POS_X_WPRINT TETRIS_PLAY_BOARD_POS_X_WPRINT + 5
#define TETRIS_PLAY_STATISTIC_POS_Y_WPRINT TETRIS_PLAY_SINGLE_SCREEN_POS_Y_WPRINT + 3

#define TETRIS_PLAY_STATISTIC_INTERVAL_HEIGHT (3)

#define TETRIS_PLAY_STATISTIC_TETROMINO_POS_X_WPRINT (TETRIS_PLAY_STATISTIC_POS_X_WPRINT - TETRIS_PLAY_STATISTIC_INTERVAL_HEIGHT + 1)
#define TETRIS_PLAY_STATISTIC_TETROMINO_POS_Y_WPRINT (TETRIS_PLAY_STATISTIC_POS_Y_WPRINT + 2)

void init_tetris_play_statistics(tetris_play_statistic_t* const out_st);
void wdraw_tetris_play_statistics(const tetris_play_statistic_t* st, const block_wprint_set_t* set);
void inc_tetromino_cnt(tetris_play_statistic_t* const out_st, symbol_id_t id);

#endif /* __TETRIS_PLAY_TETROMINO_STATISTIC__H */
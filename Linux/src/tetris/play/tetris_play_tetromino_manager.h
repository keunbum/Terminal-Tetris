#ifndef __TETRIS_PLAY_TETROMINO_MANAGER__H
#define __TETRIS_PLAY_TETROMINO_MANAGER__H

#include <stdlib.h>

#include "tetris_play_tetromino_generator.h"
#include "tetris/scene/tetris_play_screen.h"
#include "tetris/object/board.h"

#define TETROMINO_MANAGER_QUEUE_MAX_SIZE (5)

#define TETRIS_PLAY_TETROMINO_MANAGER_POS_X (TETRIS_PLAY_SINGLE_SCREEN_POS_X + 5)
#define TETRIS_PLAY_TETROMINO_MANAGER_POS_Y (TETRIS_PLAY_SINGLE_SCREEN_POS_Y + (TETRIS_PLAY_SINGLE_SCREEN_WIDTH + TETRIS_PLAY_BOARD_WIDTH) / 2 + 5)

#define TETRIS_PLAY_TETROMINO_MANAGER_POS_X_WPRINT (TETRIS_PLAY_SINGLE_SCREEN_POS_X_WPRINT + 6)
#define TETRIS_PLAY_TETROMINO_MANAGER_POS_Y_WPRINT (TETRIS_PLAY_SINGLE_SCREEN_POS_Y_WPRINT + (TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT + TETRIS_PLAY_BOARD_WIDTH_WPRINT) / 2 + 4)

#define TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_HEIGHT_WPRINT (4 * TETROMINO_MANAGER_QUEUE_MAX_SIZE + 2)
#define TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_WIDTH_WPRINT ((TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT - TETRIS_PLAY_BOARD_WIDTH_WPRINT) / 2 - 5)


/* Implements an index-based circular queue. */
typedef struct {
    // const pos_t que_pos;
    const pos_t que_pos_wprint;

    int max_size;
    int beg;
    int end;
    int cnt;
    tetromino_t* que;

    tetromino_t main;
    tetromino_t hold;
    tetromino_generator_t tetro_gen;
} tetromino_manager_t;

static inline const tetromino_t* top_tetromino(const tetromino_manager_t* man)
{
    my_assert(man->cnt > 0);
    return man->que + man->beg;
}

static inline void push_tetromino(tetromino_manager_t* const out_man, tetromino_t tetro)
{
    my_assert(out_man->cnt < out_man->max_size);
    out_man->que[out_man->end] = tetro;
    /* I know this way to be faster than the remainder operator. */
    if (++out_man->end == out_man->max_size) {
        out_man->end = 0;
    }
    out_man->cnt += 1;
}

static inline tetromino_t pop_tetromino(tetromino_manager_t* const out_man)
{
    my_assert(out_man->cnt > 0);
    tetromino_t ret = out_man->que[out_man->beg];
    if (++out_man->beg == out_man->max_size) {
        out_man->beg = 0;
    }
    out_man->cnt -= 1;
    return ret;
}

void init_tetromino_manager_malloc(tetromino_manager_t* const out_man, int max_size);
void cleanup_tetromino_manager_free(tetromino_manager_t* const out_man);
void wdraw_tetromino_manager_queue(const tetromino_manager_t* man);

#endif /* __TETRIS_PLAY_TETROMINO_MANAGER__H */
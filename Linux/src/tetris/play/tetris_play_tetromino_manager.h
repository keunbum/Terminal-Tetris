#ifndef __TETRIS_PLAY_TETROMINO_MANAGER__H
#define __TETRIS_PLAY_TETROMINO_MANAGER__H

#include <stdlib.h>

#include "fixed_queue.h"
#include "pthread_macro.h"
#include "tetris/object/board.h"
#include "tetris/object/frame.h"
#include "tetris/play/tetris_play_tetromino_statistic.h"
#include "tetris/play/tetris_play_update_tetromino_status.h"
#include "tetris/scene/tetris_play_screen.h"
#include "tetris_play_tetromino_generator.h"

#define TETROMINO_MANAGER_QUEUE_MAX_SIZE (5)

#define TETRIS_PLAY_TETROMINO_MANAGER_POS_X_WPRINT (TETRIS_PLAY_SINGLE_SCREEN_POS_X_WPRINT + 6)
#define TETRIS_PLAY_TETROMINO_MANAGER_POS_Y_WPRINT (TETRIS_PLAY_SINGLE_SCREEN_POS_Y_WPRINT + (TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT + TETRIS_PLAY_BOARD_WIDTH_WPRINT) / 2 + 2)

#define TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_HEIGHT_WPRINT (4 * TETROMINO_MANAGER_QUEUE_MAX_SIZE + 2)
#define TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_WIDTH_WPRINT ((TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT - TETRIS_PLAY_BOARD_WIDTH_WPRINT) / 2 - 5)

typedef pthread_spinlock_t tetromino_manager_lock_t;

typedef struct {
    pos_t pos_wprint;

    tetromino_t* tetro_main;
    tetromino_t* tetro_hold;
    tetromino_generator_t tetro_gen;
    tetris_play_statistic_t stat;
    fixed_queue_t que;
    frame_t frame;

    tetromino_manager_lock_t lock;
} tetromino_manager_t;

// static inline bool is_queue_empty(tetromino_manager_t* const out_man)
// {
//     return out_man->cnt == 0;
// }

// static inline const tetromino_t* get_queue_top(const tetromino_manager_t* man)
// {
//     my_assert(!is_queue_empty(man));
//     return man->pa_que[man->beg];
// }

// static inline void push_queue(tetromino_manager_t* const out_man, tetromino_t* tetro)
// {
//     my_assert(out_man->cnt < out_man->max_size);
//     out_man->pa_que[out_man->end] = tetro;
//     /* I know this way to be faster than the remainder operator. */
//     if (++out_man->end == out_man->max_size) {
//         out_man->end = 0;
//     }
//     out_man->cnt += 1;
// }

// static inline tetromino_t* pop_queue(tetromino_manager_t* const out_man)
// {
//     my_assert(!is_queue_empty(out_man));
//     tetromino_t* ret = out_man->pa_que[out_man->beg];
//     if (++out_man->beg == out_man->max_size) {
//         out_man->beg = 0;
//     }
//     out_man->cnt -= 1;
//     return ret;
// }

void init_tetromino_manager(tetromino_manager_t* const out_man, int max_size);
void cleanup_tetromino_manager_free(tetromino_manager_t* const out_man);
tetromino_try_status_t update_tetromino_manager(tetromino_manager_t* const out_man, board_t* const out_board, game_time_t delta_time);
void wdraw_tetromino_manager(const tetromino_manager_t* man);

#endif /* __TETRIS_PLAY_TETROMINO_MANAGER__H */
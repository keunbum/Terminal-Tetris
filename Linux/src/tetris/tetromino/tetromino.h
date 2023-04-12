#ifndef __TETROMINO__H
#define __TETROMINO__H

#include <stdbool.h>
#include <pthread.h>

#include "debug.h"
#include "block.h"
#include "color.h"
#include "polyomino.h"
#include "pos.h"
#include "util.h"

DECLARE_POLYOMINO_SYMBOL_T(4);

typedef polyomino_symbol_4_t tetromino_symbol_t;

typedef enum {
    DIR_BOT,
    DIR_RIGHT,
    DIR_TOP,
    DIR_LEFT,
} dir_t;

typedef int tetromino_id_t;
typedef int symbol_id_t;
typedef double velocity_t;
typedef pthread_spinlock_t tetromino_lock_t;

typedef struct {
    tetromino_id_t id;
    symbol_id_t symbol_id;
    pos_t pos;
    pos_t ground_pos;
    velocity_t velocity;
    dir_t rotate_dir;
    wchar_t block_code;
} tetromino_t;

#define TOTAL_TETROMINO_NUM_OF_KINDS (7)
#define TOTAL_DIR_NUM_OF_KINDS (4)

extern const tetromino_symbol_t G_TETROMINO_SYMBOLS[TOTAL_TETROMINO_NUM_OF_KINDS];
extern const polyomino_matrix_n_t G_TETROMINO_MATRIX_NS[TOTAL_TETROMINO_NUM_OF_KINDS];
extern const polyomino_matrix_t G_TETROMINO_MATRIXS[TOTAL_TETROMINO_NUM_OF_KINDS][TOTAL_DIR_NUM_OF_KINDS];

extern tetromino_lock_t g_tetromino_lock;

#define init_tetris_play_tetromino_lock() func_check_error(pthread_spin_init, &g_tetromino_lock, PTHREAD_PROCESS_PRIVATE)
#define tetris_play_tetromino_lock() func_check_error(pthread_spin_lock, &g_tetromino_lock)
#define tetris_play_tetromino_unlock() func_check_error(pthread_spin_unlock, &g_tetromino_lock)
#define cleanup_tetris_play_update_lock() func_check_error(pthread_spin_destroy, &g_tetromino_lock)

static inline polyomino_matrix_n_t get_tetromino_matrix_n(symbol_id_t sid)
{
    return G_TETROMINO_MATRIX_NS[(int)sid];
}

static inline polyomino_matrix_t get_tetromino_matrix(symbol_id_t sid, dir_t rotate_dir)
{
    my_assert(0 <= sid && sid < TOTAL_TETROMINO_NUM_OF_KINDS);
    my_assert(0 <= rotate_dir && rotate_dir < TOTAL_DIR_NUM_OF_KINDS);
    return G_TETROMINO_MATRIXS[(int)sid][(int)rotate_dir];
}

// void init_a_tetromino(tetromino_t* const, tetromino_id_t, symbol_id_t, pos_t, velocity_t, dir_t, wchar_t);

#endif /* __TETROMINO__H */

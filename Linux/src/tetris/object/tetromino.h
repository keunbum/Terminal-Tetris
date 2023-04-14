#ifndef __TETROMINO__H
#define __TETROMINO__H

#include <pthread.h>
#include <stdbool.h>

#include "block.h"
#include "block_wprint.h"
#include "debug.h"
#include "pos.h"
#include "tetris_play_object.h"
#include "util.h"

typedef int tetromino_matrix_t;
typedef int tetromino_matrix_n_t;

static inline bool is_empty_block(tetromino_matrix_t m, int pos)
{
    return ((m >> pos) & 1) == 0;
}

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
    tetromino_id_t id; // 0-based
    symbol_id_t symbol_id; // 0-based
    pos_t pos;
    dir_t dir;
    velocity_t velocity;
    block_t block;

    // updatable_func_t update;
    // drawable_func_t draw;
} tetromino_t;

#define TOTAL_TETROMINO_NUM_OF_KINDS (7)
#define TOTAL_DIR_NUM_OF_KINDS (4)
#define TETROMINO_INIT_DIR (DIR_BOT)

extern const tetromino_matrix_n_t G_TETROMINO_MATRIX_NS[TOTAL_TETROMINO_NUM_OF_KINDS];
extern const tetromino_matrix_t G_TETROMINO_MATRIXS[TOTAL_TETROMINO_NUM_OF_KINDS][TOTAL_DIR_NUM_OF_KINDS];
extern tetromino_lock_t g_tetromino_lock;

/* -----------------------------------------------------------------------------------------*/

#define init_tetris_play_tetromino_lock() func_check_error(pthread_spin_init, &g_tetromino_lock, PTHREAD_PROCESS_PRIVATE)
#define tetris_play_tetromino_lock() func_check_error(pthread_spin_lock, &g_tetromino_lock)
#define tetris_play_tetromino_unlock() func_check_error(pthread_spin_unlock, &g_tetromino_lock)
#define cleanup_tetris_play_update_lock() func_check_error(pthread_spin_destroy, &g_tetromino_lock)

static inline tetromino_matrix_n_t get_tetromino_matrix_n(symbol_id_t sid)
{
    return G_TETROMINO_MATRIX_NS[(int)sid];
}

static inline tetromino_matrix_t get_tetromino_matrix(symbol_id_t sid, dir_t dir)
{
    my_assert(0 <= sid && sid < TOTAL_TETROMINO_NUM_OF_KINDS);
    my_assert(0 <= dir && dir < TOTAL_DIR_NUM_OF_KINDS);

    return G_TETROMINO_MATRIXS[(int)sid][(int)dir];
}

static inline pos_t get_tetromino_pos(const tetromino_t* tetro)
{
    tetris_play_tetromino_lock();
    pos_t ret = tetro->pos;
    tetris_play_tetromino_unlock();
    return ret;
}

static inline void set_tetromino_pos(tetromino_t* const out_tetro, pos_t pos)
{
    tetris_play_tetromino_lock();
    out_tetro->pos = pos;
    tetris_play_tetromino_unlock();
}

static inline dir_t get_tetromino_dir(const tetromino_t* tetro)
{
    tetris_play_tetromino_lock();
    dir_t ret = tetro->dir;
    tetris_play_tetromino_unlock();
    return ret;
}

static inline void set_tetromino_dir(tetromino_t* const out_tetro, dir_t dir)
{
    tetris_play_tetromino_lock();
    out_tetro->dir = dir;
    tetris_play_tetromino_unlock();
}

// typedef void (*tetromino_traverse_func_t)(int i, int j, void* arg);
// void traverse_tetromino(const tetromino_t* tetro, tetromino_traverse_func_t func, void* arg);

#endif /* __TETROMINO__H */

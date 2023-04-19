#ifndef __TETROMINO__H
#define __TETROMINO__H

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

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
#define TETROMINO_INIT_DIR (DIR_BOT)

static inline const wchar_t* get_dir_wstr(dir_t status)
{
    if (status == DIR_BOT) {
        return L"DIR_BOT";
    }
    if (status == DIR_RIGHT) {
        return L"DIR_RIGHT";
    }
    if (status == DIR_TOP) {
        return L"DIR_TOP";
    }
    if (status == DIR_LEFT) {
        return L"DIR_LEFT";
    }
    my_assert(false);
}

typedef int symbol_id_t;

typedef float velocity_t;

typedef struct tetromino_t tetromino_t;
struct tetromino_t {
    int id; // for debug
    symbol_id_t symbol_id;
    dir_t dir;
    pos_t pos;
    pos_t pos_wprint;
    velocity_t velocity;
    block_t block;
    tetromino_t* prev_drawn;
};
#define TETROMINO_NUM_OF_KINDS (7)
#define DIR_NUM_OF_KINDS (4)

static inline wchar_t get_symbol_wstr(symbol_id_t symbol_id)
{
    static const wchar_t S_ID2SYMBOL[TETROMINO_NUM_OF_KINDS] = { L'I', L'O', L'T', L'J', L'L', L'S', L'Z'};
    return S_ID2SYMBOL[symbol_id];
}

#ifdef TETRIS_DEBUG
static inline void debug_tetromino(const tetromino_t* tetro)
{
    ewprintf("For tetro-%d\n", tetro->id);
    ewprintf("symbol: %lc\n", get_symbol_wstr(tetro->symbol_id));
    ewprintf("dir: %ls\n", get_dir_wstr(tetro->dir));
    ewprintf("pos: (%d, %d)\n", (int)tetro->pos.x, (int)tetro->pos.y);
}
#endif

extern const tetromino_matrix_n_t G_TETROMINO_MATRIX_NS[TETROMINO_NUM_OF_KINDS];
extern const tetromino_matrix_t G_TETROMINO_MATRIXS[TETROMINO_NUM_OF_KINDS][DIR_NUM_OF_KINDS];

/* -----------------------------------------------------------------------------------------*/

static inline bool is_first_drawn_tetromino(const tetromino_t* tetro)
{
    my_assert(tetro != NULL);

    return tetro->prev_drawn == NULL;
}

static inline bool is_valid_tetromino(const tetromino_t* tetro)
{
    return tetro != NULL;
}

static inline tetromino_matrix_n_t get_tetromino_matrix_n(symbol_id_t sid)
{
    return G_TETROMINO_MATRIX_NS[(int)sid];
}

static inline tetromino_matrix_t get_tetromino_matrix(symbol_id_t sid, dir_t dir)
{
    my_assert(0 <= sid && sid < TETROMINO_NUM_OF_KINDS);
    my_assert(0 <= dir && dir < DIR_NUM_OF_KINDS);

    return G_TETROMINO_MATRIXS[(int)sid][(int)dir];
}

static inline tetromino_t* create_tetromino_empty_malloc(void)
{
    return (tetromino_t*)malloc(sizeof(tetromino_t));
}

void save_tetromino_tobedrawn(tetromino_t* const out_tetro, block_wprint_t clean_wprint);
void cleanup_tetromino_free(tetromino_t* const out_tetro);

tetromino_t* init_tetromino_malloc(int id, symbol_id_t symbol_id, dir_t dir, pos_t pos, velocity_t velocity, block_t block, tetromino_t* prev_drawn);
tetromino_t* init_tetromino_poswprint_malloc(int id, symbol_id_t symbol_id, dir_t dir, pos_t pos_wprint, velocity_t velocity, block_t block, tetromino_t* prev_drawn);

#endif /* __TETROMINO__H */

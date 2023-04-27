#ifndef __TETROMINO__H
#define __TETROMINO__H

#include <stdbool.h>
#include <stdlib.h>

#include "block.h"
#include "block_wprint.h"
#include "debug.h"
#include "pos.h"
#include "tetris_play_object.h"
#include "util.h"

typedef int tetromino_symbol_t;

typedef enum {
    DIR_BOT,
    DIR_RIGHT,
    DIR_TOP,
    DIR_LEFT,
} dir_t;
#define TETROMINO_INIT_DIR (DIR_BOT)
#define DIR_NUM_OF_KINDS (4)

typedef int symbol_id_t;
typedef float velocity_t;
typedef struct tetromino tetromino_t;

struct tetromino {
    int id; // for debug
    symbol_id_t symbol_id;
    dir_t dir;
    pos_t pos;
    pos_t next_pos_wprint;
    velocity_t velocity;
    block_t block;
    block_wprint_t clean_wprint;
    tetromino_t* prev_drawn;
};
#define TETROMINO_NUM_OF_KINDS (7)

extern const tetromino_symbol_t G_TETROMINO_SYMBOLS[TETROMINO_NUM_OF_KINDS][DIR_NUM_OF_KINDS];

/* -----------------------------------------------------------------------------------------*/

static inline bool is_full_block(tetromino_symbol_t m, int pos)
{
    return (m >> pos) & 1;
}

#define traverse_symbol(i, j, symbol) \
    for (int i = 0; i < 4; ++i)       \
        for (int j = 0; j < 4; ++j)   \
            if (is_full_block(symbol, i * 4 + j))

static inline bool is_first_drawn_tetromino(const tetromino_t* tetro)
{
    my_assert(tetro != NULL);

    return tetro->prev_drawn == NULL;
}

static inline bool is_valid_tetromino(const tetromino_t* tetro)
{
    return tetro != NULL;
}

static inline tetromino_symbol_t get_tetromino_symbol(symbol_id_t sid, dir_t dir)
{
    my_assert(0 <= sid && sid < TETROMINO_NUM_OF_KINDS);
    my_assert(0 <= dir && dir < DIR_NUM_OF_KINDS);

    return G_TETROMINO_SYMBOLS[sid][dir];
}

static inline void update_tetromino_pos(tetromino_t* const out_tetro, pos_t pos)
{
    out_tetro->pos = pos;
    out_tetro->next_pos_wprint = get_pos_wprint(out_tetro->pos);
}

static inline tetromino_t* create_tetromino_empty_malloc(void)
{
    return (tetromino_t*)malloc(sizeof(tetromino_t));
}

const wchar_t* get_dir_wstr(dir_t dir);
wchar_t get_symbol_wch(symbol_id_t symbol_id);
void save_tetromino_tobedrawn(tetromino_t* const out_tetro);
void cleanup_tetromino_free(tetromino_t* const out_tetro);

tetromino_t* init_tetromino_malloc(int id, symbol_id_t symbol_id, dir_t dir, pos_t pos, velocity_t velocity, block_t block, block_wprint_t clean_wprint, tetromino_t* prev_drawn);
tetromino_t* init_tetromino_poswprint_malloc(int id, symbol_id_t symbol_id, dir_t dir, pos_t next_pos_wprint, velocity_t velocity, block_t block, block_wprint_t clean_wprint, tetromino_t* prev_drawn);

#ifdef TETRIS_DEBUG
static inline void debug_tetromino(const tetromino_t* tetro)
{
    ewprintf("For tetro-%d\n", tetro->id);
    ewprintf("symbol: %lc\n", get_symbol_wch(tetro->symbol_id));
    ewprintf("dir: %ls\n", get_dir_wstr(tetro->dir));
    ewprintf("pos: (%d, %d)\n", (int)tetro->pos.x, (int)tetro->pos.y);
}
#endif

#endif /* __TETROMINO__H */

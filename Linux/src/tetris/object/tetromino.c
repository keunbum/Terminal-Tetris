#include <time.h>

#include "debug.h"
#include "tetromino.h"

/* Should I just unify it to 4? */
const tetromino_matrix_n_t G_TETROMINO_MATRIX_NS[TETROMINO_NUM_OF_KINDS] = {
    4, 2, 3, 3, 3, 3, 3
};

const tetromino_matrix_t G_TETROMINO_MATRIXS[TETROMINO_NUM_OF_KINDS][DIR_NUM_OF_KINDS] = {
    { 0x00F0, 0x2222, 0x0F00, 0x4444 }, // I
    { 0x000F, 0x000F, 0x000F, 0x000F }, // O
    { 0x003A, 0x009A, 0x00B8, 0x00B2 }, // T
    { 0x01C8, 0x01A4, 0x0027, 0x004B }, // J
    { 0x01E0, 0x0126, 0x000F, 0x00C9 }, // L
    { 0x00F0, 0x0132, 0x001E, 0x0099 }, // S
    { 0x0198, 0x00B4, 0x0033, 0x005A }, // Z
};

static void init_tetromino(tetromino_t* const out_tetro,
    int id, symbol_id_t symbol_id, dir_t dir, pos_t pos, pos_t pos_wprint, velocity_t velocity, block_t block, tetromino_t* prev_drawn)
{
    debug();

    out_tetro->id = id;
    out_tetro->symbol_id = symbol_id;
    out_tetro->dir = dir;
    out_tetro->pos = pos;
    out_tetro->pos_wprint = pos_wprint;
    out_tetro->velocity = velocity;
    out_tetro->block = block;
    out_tetro->prev_drawn = prev_drawn;

    ewprintf("tetro-%d has been spawned\n", out_tetro->id);
}

void cleanup_tetromino(tetromino_t* const out_tetro)
{
    if (out_tetro == NULL) {
        return;
    }
    if (out_tetro->prev_drawn != NULL) {
        free(out_tetro->prev_drawn);
        out_tetro->prev_drawn = NULL;
    }
    free(out_tetro);
}

tetromino_t* init_tetromino_malloc(int id, symbol_id_t symbol_id, dir_t dir, pos_t pos, velocity_t velocity, block_t block, tetromino_t* prev_drawn)
{
    tetromino_t* pa_tetro = create_tetromino_empty_malloc();
    init_tetromino(pa_tetro, id, symbol_id, dir, pos, create_pos_empty(), velocity, block, prev_drawn);
    return pa_tetro;
}

tetromino_t* init_tetromino_poswprint_malloc(int id, symbol_id_t symbol_id, dir_t dir, pos_t pos_wprint, velocity_t velocity, block_t block, tetromino_t* prev_drawn)
{
    tetromino_t* pa_tetro = create_tetromino_empty_malloc();
    init_tetromino(pa_tetro, id, symbol_id, dir, create_pos_empty(), pos_wprint, velocity, block, prev_drawn);
    return pa_tetro;
}

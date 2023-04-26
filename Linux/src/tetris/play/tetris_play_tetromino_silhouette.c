#include <assert.h>

#include "tetris_play_tetromino_silhouette.h"
#include "debug.h"
#include "tetris_play_update_tetromino_status.h"

#define TETRIS_PLAY_TETROMINO_BLOCK_SILHOUETTE_WPRINT BLOCK_WPRINT_LIGHT_LARGE_SQUARE

pos_t get_tetromino_silhouette_pos(const board_t* board, const tetromino_t* tetro)
{
    debug();

    for (pos_int_t cpos = get_posint(tetro->pos); cpos.x < board->pos.x + board->height; ++cpos.x) {
        pos_int_t npos = { cpos.x + 1, cpos.y };
        if (!is_ok_tetromino_next_status(board, tetro, npos, tetro->dir)) {
            return get_pos(cpos);
        }
    }
    my_assert(false);
    pos_t ret = {};
    return ret;
}

void init_tetromino_silhouette(tetromino_t* const out_tetro)
{
    out_tetro->prev_drawn = NULL;
}


void cleanup_tetromino_silhouette(tetromino_t* const out_tetro)
{
    if (out_tetro->prev_drawn != NULL) {
        free(out_tetro->prev_drawn);
        out_tetro->prev_drawn = NULL;
    }
}

void update_tetromino_silhouette(tetromino_t* const restrict out_tetro_des, const tetromino_t* restrict tetro_src, block_wprint_t init_block_wprint)
{
    debug();

    my_assert(out_tetro_des != NULL);
    my_assert(tetro_src != NULL);

    out_tetro_des->symbol_id = tetro_src->symbol_id;
    out_tetro_des->block.wprint = init_block_wprint;
    out_tetro_des->clean_wprint = BLOCK_WPRINT_WHITE_LARGE_SQUARE;
    // out_tetro_des->prev_drawn = NULL;
}

void update_tetromino_silhouette_dir_pos(tetromino_t* const restrict out_tetro_des, const tetromino_t* restrict tetro_src, const board_t* board)
{
    debug();

    my_assert(out_tetro_des != NULL);
    my_assert(tetro_src != NULL);

    out_tetro_des->dir = tetro_src->dir;
    update_tetromino_pos(out_tetro_des, get_tetromino_silhouette_pos(board, tetro_src));
}

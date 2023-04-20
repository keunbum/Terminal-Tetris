#include <assert.h>

#include "tetris_play_tetromino_silhouette.h"
#include "debug.h"
#include "tetris_play_update_tetromino_status.h"

#define TETRIS_PLAY_TETROMINO_BLOCK_SILHOUETTE_WPRINT BLOCK_WPRINT_LIGHT_LARGE_SQUARE

pos_t get_tetromino_silhouette_pos(board_t* const restrict out_board, const tetromino_t* restrict tetro)
{
    debug();

    pos_t ret = {};
    for (pos_int_t cpos = get_posint(tetro->pos); cpos.x <= out_board->pos.x + out_board->height; ++cpos.x) {
        pos_int_t npos = { cpos.x + 1, cpos.y };
        tetromino_try_status_t res = try_tetromino_next_status(out_board, tetro, npos, tetro->dir);
        if (res == TETROMINO_TRY_STATUS_ONTHEGROUND) {
            return get_pos(cpos);
        }
    }
    my_assert(false);
    return ret;
}

tetromino_t get_tetromino_silhouette(board_t* const restrict out_board, const tetromino_t* restrict tetro)
{
    debug();

    pos_t res = get_tetromino_silhouette_pos(out_board, tetro);
    tetromino_t ret = {};
    ret.symbol_id = tetro->symbol_id;
    ret.pos = res;
    ret.dir = tetro->dir;
    ret.block.nature = BLOCK_NATURE_EMPTY;
    ret.block.wprint = TETRIS_PLAY_TETROMINO_BLOCK_SILHOUETTE_WPRINT;
    return ret;
}

#include "tetris_play_tetromino_silhouette.h"
#include "debug.h"
#include "tetris_play_update_tetromino_status.h"

#define TETRIS_PLAY_TETROMINO_BLOCK_SILHOUETTE_WPRINT BLOCK_WPRINT_LIGHT_LARGE_SQUARE

tetromino_t get_tetromino_silhouette(board_t* const restrict out_board, const tetromino_t* restrict tetro)
{
    debug();

    tetromino_t ret = {};
    for (pos_t cground_pos = tetro->pos; cground_pos.x < out_board->height; ++cground_pos.x) {
        pos_t nground_pos = { cground_pos.x + 1, cground_pos.y };
        tetromino_try_status_t res = try_tetromino_next_status(out_board, tetro, nground_pos, tetro->dir);
        if (res != TETROMINO_TRY_STATUS_MOVED) {
            ret.symbol_id = tetro->symbol_id;
            ret.pos = cground_pos;
            ret.dir = tetro->dir;
            ret.block.nature = BLOCK_NATURE_EMPTY;
            ret.block.wprint = TETRIS_PLAY_TETROMINO_BLOCK_SILHOUETTE_WPRINT;
            return ret;
        }
    }
    my_assert(false);
    return ret;
}
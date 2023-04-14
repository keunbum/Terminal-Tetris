#include <assert.h>
#include <stdbool.h>

#include "tetris_play_tetromino_silhouette.h"
#include "tetris_play_update_tetromino_status.h"

tetromino_t get_tetromino_silhouette(const board_t* board, const tetromino_t* tetro)
{
    debug();

    bool ok = false;
    tetromino_t ret;
    for (pos_t cground_pos = tetro->pos; cground_pos.x < board->height; ++cground_pos.x) {
        pos_t nground_pos = { cground_pos.x + 1, cground_pos.y };
        tetromino_try_status_t res = try_tetromino_next_status(board, tetro, nground_pos, tetro->dir);
        if (res != TETROMINO_TRY_STATUS_MOVED) {
            ret.id = -2;
            ret.symbol_id = tetro->symbol_id;
            ret.pos = cground_pos;
            ret.dir = tetro->dir;
            ret.block_code = TETRIS_PLAY_TETROMINO_BLOCK_SILHOUETTE_WPRINT;
            ok = true;
            break;
        }
    }
    assert(ok);
    return ret;
}
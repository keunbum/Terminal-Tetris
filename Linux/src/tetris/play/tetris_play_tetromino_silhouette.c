#include <assert.h>
#include <stdlib.h>

#include "tetris_play_tetromino_silhouette.h"
#include "debug.h"
#include "tetris_play_update_tetromino_status.h"

#define TETRIS_PLAY_TETROMINO_BLOCK_SILHOUETTE_WPRINT BLOCK_WPRINT_LIGHT_LARGE_SQUARE

pos_t get_tetromino_silhouette_pos(const board_t* board, const tetromino_t* tetro)
{
    debug();
    int cpos_y = (int) tetro->pos.y;
    for (int cpos_x = (int) tetro->pos.x; cpos_x < board->pos.x + board->height; ++cpos_x) {
        if (!is_ok_tetromino_next_status(board, tetro, create_posint(cpos_x + 1, cpos_y), tetro->dir)) {
            return create_pos((pos_e_t)cpos_x, (pos_e_t)cpos_y);
        }
    }
    my_assert(false);
    return (pos_t){};
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

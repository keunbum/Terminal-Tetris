#include <assert.h>
#include <stdlib.h>

#include "tetris_play_ghost_piece.h"
#include "debug.h"
#include "tetris_play_update_tetromino_status.h"

pos_t get_ghost_piece_pos(const board_t* board, const tetromino_t* tetro)
{
    int cpos_y = (int) tetro->pos.y;
    for (int cpos_x = (int) tetro->pos.x; cpos_x < board->pos.x + board->height; ++cpos_x) {
        if (!is_ok_tetromino_next_status(board, tetro, create_posint(cpos_x + 1, cpos_y), tetro->dir)) {
            return create_pos((pos_e_t)cpos_x, (pos_e_t)cpos_y);
        }
    }
    my_assert(false);
    return (pos_t){};
}

void init_ghost_piece(tetromino_t* const out_tetro)
{
    out_tetro->prev_drawn = NULL;
}


void cleanup_ghost_piece(tetromino_t* const out_tetro)
{
    if (out_tetro->prev_drawn != NULL) {
        free(out_tetro->prev_drawn);
        out_tetro->prev_drawn = NULL;
    }
}

#include <assert.h>
#include <stdlib.h>

#include "tetris_play_ghost_piece.h"
#include "debug.h"
#include "tetris_play_update_tetromino_in_play_status.h"

pos_t get_ghost_piece_pos(const matrix_t* matrix, const tetromino_t* tetro)
{
    int cpos_y = (int) tetro->pos.y;
    for (int cpos_x = (int) tetro->pos.x; cpos_x < matrix->pos.x + matrix->height; ++cpos_x) {
        if (!is_ok_tetromino_in_play_next_status(matrix, tetro, create_posint(cpos_x + 1, cpos_y), tetro->dir)) {
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

#ifndef __TETRIS_PLAY_GHOST_PIECE__H
#define __TETRIS_PLAY_GHOST_PIECE__H

#include "tetris/object/matrix.h"
#include "tetris/object/tetromino.h"

#define GHOST_PIECE_BLOCK_WPRINT BLOCK_WPRINT_BLACK_SQUARE_BUTTON

pos_t get_ghost_piece_pos(const matrix_t* matrix, const tetromino_t* tetro);
void init_ghost_piece(tetromino_t* const out_tetro);
void cleanup_ghost_piece(tetromino_t* const out_tetro);

static inline void update_ghost_piece_with(tetromino_t* const restrict out_tetro_des, const tetromino_t* restrict tetro_src, block_wprint_t init_block_wprint)
{
    my_assert(out_tetro_des != NULL);
    my_assert(tetro_src != NULL);

    out_tetro_des->shape_id = tetro_src->shape_id;
    out_tetro_des->block.wprint = init_block_wprint;
    out_tetro_des->clean_wprint = MATRIX_INNTER_BLOCK_WPRINT;
}

static inline void update_ghost_piece(tetromino_t* const restrict out_tetro_des, const tetromino_t* restrict tetro_src)
{
    update_ghost_piece_with(out_tetro_des, tetro_src, GHOST_PIECE_BLOCK_WPRINT);
}

static inline void update_ghost_piece_dir_pos(tetromino_t* const restrict out_tetro_des, const tetromino_t* restrict tetro_src, const matrix_t* matrix)
{
    my_assert(out_tetro_des != NULL);
    my_assert(tetro_src != NULL);

    out_tetro_des->dir = tetro_src->dir;
    update_tetromino_pos(out_tetro_des, get_ghost_piece_pos(matrix, tetro_src));
}

#endif /* __TETRIS_PLAY_GHOST_PIECE__H */
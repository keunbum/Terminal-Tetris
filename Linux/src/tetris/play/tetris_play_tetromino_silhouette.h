#ifndef __TETRIS_PLAY_TETROMINO_SILHOUETTE__H
#define __TETRIS_PLAY_TETROMINO_SILHOUETTE__H

#include "tetris/object/board.h"
#include "tetris/object/tetromino.h"

pos_t get_tetromino_silhouette_pos(const board_t* board, const tetromino_t* tetro);

void init_tetromino_silhouette(tetromino_t* const out_tetro);
void cleanup_tetromino_silhouette(tetromino_t* const out_tetro);

void update_tetromino_silhouette(tetromino_t* const restrict out_tetro_des, const tetromino_t* restrict tetro_src, block_wprint_t init_block_wprint);
void update_tetromino_silhouette_dir_pos(tetromino_t* const restrict out_tetro_des, const tetromino_t* restrict tetro_src, const board_t* board);
void cleanup_tetromino_silhouette(tetromino_t* const out_tetro);

#endif /* __TETRIS_PLAY_TETROMINO_SILHOUETTE__H */
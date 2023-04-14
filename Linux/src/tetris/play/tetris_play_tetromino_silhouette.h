#ifndef __TETRIS_PLAY_TETROMINO_SILHOUETTE__H
#define __TETRIS_PLAY_TETROMINO_SILHOUETTE__H

#include "tetris/object/board.h"
#include "tetris/object/tetromino.h"

tetromino_t get_tetromino_silhouette(board_t* const restrict out_board, const tetromino_t* restrict tetro);

#endif /* __TETRIS_PLAY_TETROMINO_SILHOUETTE__H */
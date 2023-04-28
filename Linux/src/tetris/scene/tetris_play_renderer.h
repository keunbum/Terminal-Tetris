#ifndef __TETRIS_PLAY_RENDERER__H
#define __TETRIS_PLAY_RENDERER__H

#include "tetris/object/tetromino.h"
#include "tetris/play/tetris_play_manager.h"

void wdraw_a_tetromino(tetromino_t* const out_tetro);
void wdraw_a_tetromino_with_silhouette(tetromino_t* const out_tetro, tetromino_t* const out_tetro_silhou, const board_t* board);
void render_out(tetris_play_manager_t* const out_man);

#endif /* __TETRIS_PLAY_RENDERER__H */
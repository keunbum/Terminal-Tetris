#ifndef __TETRIS_PLAY_RENDERER__H
#define __TETRIS_PLAY_RENDERER__H

#include "tetris/object/tetromino.h"
#include "tetris/tetris_play_manager.h"

void render_out(tetris_play_manager_t* const out_man);
void wdraw_a_tetromino_at_wprint_r(const tetromino_t* tetro, pos_t pos_wprint);

#endif /* __TETRIS_PLAY_RENDERER__H */
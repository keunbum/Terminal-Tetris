#ifndef __RENDERER__H
#define __RENDERER__H

#include "tetris/tetris_play_manager.h"
#include "tetris/tetromino/tetromino.h"

void render_out(tetris_play_manager_t* const out_play_manager);
void draw_a_tetromino_at_wprint_r(const tetromino_t* tetro, pos_t pos_wprint);

#endif /* __RENDERER__H */
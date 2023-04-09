#ifndef __RENDERER__H
#define __RENDERER__H

#include "tetris/tetromino/tetromino.h"

void erase_a_tetromino_r(const tetromino_t*);
void draw_a_tetromino_r(const tetromino_t*);
void render_out(void);

void new_erase_a_tetromino_r(const tetromino_t* tetro);
void new_draw_a_tetromino_r(const tetromino_t* tetro);
void new_render_out(void);

void draw_a_tetromino_mainbody_at_wprint_r(const tetromino_t* tetro, pos_t pos_wprint);

#endif /* __RENDERER__H */
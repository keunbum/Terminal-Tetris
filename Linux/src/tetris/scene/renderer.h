#ifndef __RENDERER__H
#define __RENDERER__H

#include "tetris/tetromino/tetromino.h"

void erase_a_tetromino_r(const tetromino_t*);
void draw_a_tetromino_r(const tetromino_t*);
void render_out(void);

#endif /* __RENDERER__H */
#ifndef __TETRIS_PLAY_SCENE__H
#define __TETRIS_PLAY_SCENE__H

#include "draw/draw_tool.h"
#include "tetris/play/tetris_play_board.h"
#include "tetris/tetris_play_manager.h"
#include "tetris_play_screen.h"

int load_tetris_play_scene(tetris_play_mode_t, int, int);
void cleanup_tetris_play_scene(void);

#endif /* __TETRIS_PLAY_SCENE__H */
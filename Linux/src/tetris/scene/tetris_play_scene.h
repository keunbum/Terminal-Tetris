#ifndef __TETRIS_PLAY_SCENE__H
#define __TETRIS_PLAY_SCENE__H

#include "draw/draw_tool.h"
#include "tetris/physics/tetris_play_board.h"
#include "tetris_play_screen.h"

typedef enum {
    TETRIS_PLAY_MODE_SINGLE,
    TETRIS_PLAY_MODE_MULTI,
} tetris_play_mode_t;

#define TETRIS_PLAY_BOARD_START_POS_X_WPRINT \
    (TETRIS_PLAY_SINGLE_SCREEN_START_POS_X_WPRINT + (TETRIS_PLAY_SINGLE_SCREEN_HEIGHT_WPRINT - TETRIS_PLAY_BOARD_HEIGHT_WPRINT) / 2 + 4)

#define TETRIS_PLAY_BOARD_START_POS_Y_WPRINT \
    (TETRIS_PLAY_SINGLE_SCREEN_START_POS_Y_WPRINT + (TETRIS_PLAY_SINGLE_SCREEN_WIDTH_WPRINT - TETRIS_PLAY_BOARD_WIDTH_WPRINT) / 2 - 1)

int load_tetris_play_scene(tetris_play_mode_t, int, int);

#endif /* __TETRIS_PLAY_SCENE__H */
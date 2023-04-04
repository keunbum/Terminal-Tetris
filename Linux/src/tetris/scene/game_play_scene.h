#ifndef __GAME_PLAY_UI__H
#define __GAME_PLAY_UI__H

#include "draw/draw_tool.h"
#include "tetris/physics/game_board.h"
#include "game_play_screen.h"

#define GAME_PLAY_MODE_SINGLE (1)
#define GAME_PLAY_MODE_MULTI (2)

#define GAME_PLAY_BOARD_START_POS_X_WPRINT \
    (GAME_PLAY_SINGLE_SCREEN_START_POS_X_WPRINT + (GAME_PLAY_SINGLE_SCREEN_HEIGHT_WPRINT - GAME_PLAY_BOARD_HEIGHT_WPRINT) / 2 + 4)

#define GAME_PLAY_BOARD_START_POS_Y_WPRINT \
    (GAME_PLAY_SINGLE_SCREEN_START_POS_Y_WPRINT + (GAME_PLAY_SINGLE_SCREEN_WIDTH_WPRINT - GAME_PLAY_BOARD_WIDTH_WPRINT) / 2 - 1)

int load_game_play_scene(int, int, int);

#endif /* __GAME_PLAY_UI__H */
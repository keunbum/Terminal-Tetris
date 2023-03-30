#ifndef __GAME_PLAY_UI__H
#define __GAME_PLAY_UI__H

#include "draw_tool/draw_tool.h"
#include "game/game_play/physics/game_board.h"
#include "game/game_play/ui/game_play_screen.h"

#define GAME_PLAY_MODE_SINGLE (1)
#define GAME_PLAY_MODE_MULTI (2)

#define GAME_PLAY_BOARD_START_POS_X_IN_WPRINT \
    (GAME_PLAY_SINGLE_SCREEN_START_POS_X_IN_WPRINT + (GAME_PLAY_SINGLE_SCREEN_HEIGHT_IN_WPRINT - GAME_PLAY_BOARD_HEIGHT_IN_WPRINT) / 2 + 4)

#define GAME_PLAY_BOARD_START_POS_Y_IN_WPRINT \
    (GAME_PLAY_SINGLE_SCREEN_START_POS_Y_IN_WPRINT + (GAME_PLAY_SINGLE_SCREEN_WIDTH_IN_WPRINT - GAME_PLAY_BOARD_WIDTH_IN_WPRINT) / 2 - 1)

void wset_row_line(wchar_t* const, int, wchar_t, wchar_t, wchar_t);
int load_game_play_ui(int, int, int, int);
int load_game_play_ui_test(int game_mode, int sx, int sy, int screen_height);

#endif /* __GAME_PLAY_UI__H */
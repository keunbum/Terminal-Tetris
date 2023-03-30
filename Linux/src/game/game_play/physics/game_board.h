#ifndef __GAME_BOARD__H
#define __GAME_BOARD__H

#include <wchar.h>

#include "game/game_play/tetromino/tetromino.h"

#define GAME_PLAY_BOARD_HEIGHT (20)
#define GAME_PLAY_BOARD_WIDTH (10)

#define GAME_PLAY_BOARD_HEIGHT_IN_WPRINT (GAME_PLAY_BOARD_HEIGHT)
#define GAME_PLAY_BOARD_WIDTH_IN_WPRINT (2 * GAME_PLAY_BOARD_WIDTH)

//#define GAME_PLAY_BOARD_START_POS_X (9)
//#define GAME_PLAY_BOARD_START_POS_Y (12)

#define GAME_PLAY_BOARD_GRID_ELEMENT_DEFAULT (0)

typedef tetromino_id_t game_board_grid_element_t;

typedef struct {
    game_board_grid_element_t grid[GAME_PLAY_BOARD_HEIGHT][GAME_PLAY_BOARD_WIDTH];
} game_board_t;

extern game_board_t g_game_board;

void init_game_board(void);

#endif /* __GAME_BOARD__H */
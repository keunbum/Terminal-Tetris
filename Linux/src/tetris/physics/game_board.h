#ifndef __GAME_BOARD__H
#define __GAME_BOARD__H

#include <wchar.h>

#include "tetris/tetromino/tetromino.h"

#define GAME_PLAY_BOARD_HEIGHT (20)
#define GAME_PLAY_BOARD_WIDTH (10)

#define GAME_PLAY_BOARD_HEIGHT_WPRINT (GAME_PLAY_BOARD_HEIGHT)
#define GAME_PLAY_BOARD_WIDTH_WPRINT (2 * GAME_PLAY_BOARD_WIDTH)

#define GAME_PLAY_BOARD_GRID_ELEMENT_DEFAULT (0)

/* may be changed. */
typedef tetromino_id_t game_board_grid_element_t;

typedef struct {
    int height;
    int width;
    int height_wprint;
    int width_wprint;
    game_board_grid_element_t grid[GAME_PLAY_BOARD_HEIGHT][GAME_PLAY_BOARD_WIDTH];
} game_board_t;

void init_game_board(game_board_t* const);

#endif /* __GAME_BOARD__H */
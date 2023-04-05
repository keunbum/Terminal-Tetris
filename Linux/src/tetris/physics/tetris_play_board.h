#ifndef __TETRIS_PLAY_BOARD__H
#define __TETRIS_PLAY_BOARD__H

#include <wchar.h>

#include "tetris/tetromino/tetromino.h"

#define TETRIS_PLAY_BOARD_HEIGHT (20)
#define TETRIS_PLAY_BOARD_WIDTH (10)

#define TETRIS_PLAY_BOARD_HEIGHT_WPRINT (TETRIS_PLAY_BOARD_HEIGHT)
#define TETRIS_PLAY_BOARD_WIDTH_WPRINT (2 * TETRIS_PLAY_BOARD_WIDTH)

#define TETRIS_PLAY_BOARD_GRID_ELEMENT_DEFAULT (0)

#define TETRIS_PLAY_TETROMINO_INIT_POS_X (-5)
#define TETRIS_PLAY_TETROMINO_INIT_POS_Y (TETRIS_PLAY_BOARD_WIDTH / 2)

#define TETRIS_PLAY_TETROMINO_POS_X_MIN (TETRIS_PLAY_TETROMINO_INIT_POS_X)
#define TETRIS_PLAY_TETROMINO_POS_X_MAX (TETRIS_PLAY_BOARD_HEIGHT - 1)
#define TETRIS_PLAY_TETROMINO_POS_Y_MIN (0)
#define TETRIS_PLAY_TETROMINO_POS_Y_MAX (TETRIS_PLAY_BOARD_WIDTH - 1)

#define TETRIS_PLAY_TETROMINO_UNIT_VELOCITY (1)
#define TETRIS_PLAY_TETROMINO_INIT_VELOCITY TETRIS_PLAY_TETROMINO_UNIT_VELOCITY

/* may be changed. */
typedef tetromino_id_t game_board_grid_element_t;

typedef struct {
    int height;
    int width;
    int height_wprint;
    int width_wprint;
    game_board_grid_element_t grid[TETRIS_PLAY_BOARD_HEIGHT][TETRIS_PLAY_BOARD_WIDTH];
} game_board_t;

void init_game_board(game_board_t* const);

#endif /* __TETRIS_PLAY_BOARD__H */
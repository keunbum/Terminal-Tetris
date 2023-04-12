#include "tetris_play_board.h"
#include "debug.h"

void init_game_board(tetris_play_board_t* const board)
{
    debug();

    for (int i = 0; i < TETRIS_PLAY_BOARD_HEIGHT; ++i) {
        for (int j = 0; j < TETRIS_PLAY_BOARD_WIDTH; ++j) {
            board->grid[i][j] = TETRIS_PLAY_BOARD_GRID_ELEMENT_DEFAULT;
        }
    }
}